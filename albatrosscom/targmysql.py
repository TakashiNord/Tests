#!/usr/bin/env python
#
#-------------------------------------------------------------------------------
import os
import time
import datetime
import threading
import string
# парсер командной строки
import sys
import argparse
# работа с MySQLdb (под Win)
import MySQLdb


"""Валюты задаются 3-х буквенным кодом согласно ISO 4217"""
choice=['EUR', 'RUB', 'USD']
"""Так как кодов очень много, то такие данные лучше задавать\проверять из базы данных"""


# --orig=’EUR’ --dest=’RUB’
def createParser ():
    parser = argparse.ArgumentParser()
    ## примерный список параметров ('-o', '--orig', choices=choice, required=True, default='RUB')
    parser.add_argument ('-o', '--orig', default='RUB')
    parser.add_argument ('-d', '--dest', default='')
    return parser


# --orig=’EUR’ --dest=’RUB’
#def createParserStd ():
#    if len (sys.argv) == 1:
#        print ("Ошибка. Слишком мало параметров.")
#        return -1
#    if len (sys.argv) < 3:
#        print ("Ошибка. Слишком мало параметров.")
#        return -2
#    param_name = sys.argv[1]
#    param_value = sys.argv[2]
#    if (param_name == "--orig"):
#        print ("orig, {}!".format (param_value) )
#    else:
#        print ("Ошибка. Неизвестный параметр '{}'".format (param_name) )
#    return(0)


def connect(host, user, passwd, db):
    try:
        conn = MySQLdb.connect(host=host, user=user, passwd=passwd, db=db)
        return conn
    except :
        smsg = "---->Failed to connect to %s for %s" % (host, user)
        print(smsg)
        conn = ""
        return conn
    pass


def MainSQL():
    """  Опрос аргументов и работа с БД """
    #===================================================
    parser = createParser()
    args = parser.parse_args(sys.argv[1:])
    #print (args)
    orig = ''
    if args.orig or args.o :
        if args.orig :
            orig = format (args.orig)
        else :
            orig = format (args.o)
    #orig=orig.translate("'","")
    dest = ''
    if args.dest or args.d :
        if args.dest :
            dest = format (args.dest)
        else :
            dest = format (args.d)
    d1=dest.replace("'","")
    o1=orig.replace("'","")
    (orig,dest)=(o1,d1)
    #print ("=!=", orig , dest  )
    #===================================================
    # Проверяем есть ли база , иначе создаем
    ## host="localhost", user="root",passwd="",db="test"
    db = connect("localhost", "root", "", "dbt")
    # prepare a cursor object using cursor() method
    cursor = db.cursor()
    # Create table as per requirement
    sql = """
        select * from t
        where t.ORIG=%s and t.DEST=%s and t.DATA>(NOW() - INTERVAL 2 HOUR)
        order by 1 desc limit 1;
        """
    que= sql % (orig,dest)
    print "sql : %s " % que
    try:
        # Execute the SQL command
        cursor.execute(que)
        # Fetch a single row using fetchone() method.
        data = cursor.fetchone()
        cnt = cursor.rowcount ;
        print "Data : %s %d " % (data,cnt)
    except:
        print "Error: unable to fecth data"
        return(-1)
    if cnt>0 :
        # берем значения из БД
        print " Source   ,   Data,    Rate    "
        # Now print result
        ## формат=Источник1, дата на которую установлен курс, 1EUR = xxRUB
        print " %s, %s, 1%s=%.2f %s" % (data[1], data[2], data[3], data[5], data[4] )
    if cnt<=0 :
        # загружаем из Интернета
        print " Source   ,   Data,    Rate   "
        # Now print result
        ## формат=Источник1, дата на которую установлен курс, 1EUR = xxRUB
        print " %s, %s, 1%s=%.2f %s" % (data[1], data[2], data[3], data[5], data[4] )
    # загружаем из Интернета
    # disconnect from server
    db.close()
    return(0)


def Main():
    """Главная функция"""
    #===================================================
    now_date = datetime.date.today() # Текущая дата (без времени)
    now_time = datetime.datetime.now() # Текущая дата со временем
    cur_hour = now_time.hour # Час текущий
    cur_minute = now_time.minute # Минута текущая
    smsg = "Time run= " + now_time.strftime("%Y-%m-%d %H:%M:%S")
    #===================================================
    MainSQL()
    #===================================================
    return(0)


if __name__ == '__main__':
    Main()



