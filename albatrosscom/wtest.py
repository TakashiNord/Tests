#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------------
import os
import time
import datetime
import threading
import string
import re
# парсер командной строки
import sys
import argparse
# работа с MySQLdb (под Win)
import MySQLdb
import random
import hashlib
import shutil
import urllib2
#from urllib import urlopen
import xml.etree.ElementTree as ET
# Опрос источников - асинхронно (с использованием библиотеки gevent). 
import gevent
from gevent import monkey

reload(sys)
sys.setdefaultencoding('utf8')

""" Источники - название источника введено, для предварительного запроса в БД"""
urls = {
    'Foreign Currency Market' : 'http://www.cbr.ru/scripts/XML_daily.asp',
    'European Central Bank' : 'http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml'
}

"""Валюты задаются 3-х буквенным кодом согласно ISO 4217"""
choice=['EUR', 'RUB', 'USD']
"""Так как кодов очень много, то такие данные лучше задавать\проверять из базы данных"""


# --orig='EUR' --dest='RUB'
def createParser ():
    parser = argparse.ArgumentParser()
    ## примерный список параметров ('--orig', choices=choice, required=True, default='RUB')
    parser.add_argument ('--orig', default='RUB')
    parser.add_argument ('--dest', default='')
    return parser


def getNewSID(tag):
    ''' Build a new session ID '''
    t1 = time.time()
    time.sleep(random.random())
    t2 = time.time()
    base = hashlib.md5(tag + str(t1+t2)).hexdigest()
    return '_'.join((tag, base))


def XMLParcerDB( url , orig, dest ):
    """ Возвращаем значения """
    #===================================
    ddate="" # дата
    drate=-1 # курс
    dname="" # название Источника
    #===================================
    #print 'Starting %s' % url
    data = urllib2.urlopen(url).read()
    name1 = os.path.basename(url)
    name2 = os.path.splitext(name1)
    #print '%s \n%s \n%s bytes\n%r' % (url, name1, len(data), data[:100])
    filename1 = getNewSID(name2[0]) + name2[1] # создаем файл под случайным именем для отладки os.tempname
    # удалить временный файл
    filename2 = os.path.join(os.getcwd(), filename1)
    if os.path.exists(filename2)==True : os.remove(filename2)
    file_object = open(filename2, 'w')
    file_object.write(data)
    file_object.close( )
    tn2 = datetime.datetime.now()
    if name2[1]=='.asp' :
        tree = ET.parse(filename2)
        root = tree.getroot()
        #print "tag=%s  atr=%s" , root.tag, root.attrib
        ddate = root.get('Date')
        dtobj=datetime.datetime(*reversed(map(int,ddate.split('.'))))
        ddate = dtobj.strftime("%Y-%m-%d") + " " + tn2.strftime("%H:%M:%S")
        dname = root.get('name')
        for child in root:
            if child.find('CharCode').text==orig :
                drate = child.find('Value').text
                #print "value=%s" % child.find('Value').text
                break ;
    if name2[1]=='.xml' :
        tree = ET.parse(filename2)
        root = tree.getroot()
        #for elem in tree.iter():
            #print elem.tag, elem.attrib
        #Create an iterator
        iter = root.getiterator()
        #Iterate
        for element in iter:
            ##print "Element:", element.tag
            #Text that precedes all child elements (may be None)
            if element.text:
                text = element.text
                #if string.find(element.tag, "name")>0 : dname = repr(text)
                if re.findall("name", element.tag, re.IGNORECASE) : dname = repr(text)
            if element.keys():
                ##print "\tAttributes:"
                fl=0
                for name, value in element.items():
                    if name=='time' : ddate = value
                    if name=='currency' :
                        if value==dest : fl=1
                    if fl==1 :
                        if name=='rate' : drate = value
                    #print "\t\tName: '%s', Value: '%s'"%(name, value)
        if (ddate!="") : ddate = ddate + " " + tn2.strftime("%H:%M:%S")
    if (ddate=="") : ddate = tn2.strftime("%Y-%m-%d %H:%M:%S")
    dn1=dname.replace("'","")
    dname=dn1.encode('utf8')
    return(dname,ddate,drate)


def connect(host, user, passwd, db):
    try:
        conn = MySQLdb.connect(host="localhost", user="root", passwd="", db="dbt")
        return conn
    except :
        smsg = "---->Failed to connect to %s for %s" % (host, user)
        #print(smsg)
        conn = ""
        return conn
    pass


def MainSQLXml ( name , url, orig, dest ):
    """  """
    #===================================================
    # 2 - присоединяемся к базе
    #===================================================
    db = connect("localhost", "root", "", "dbt")
    #if db=="" : return (-2)
    # prepare a cursor object using cursor() method
    if db!="" : cursor = db.cursor()
    sql = """
        select * from t
        where t.SRC='%s' and t.ORIG='%s' and t.DEST='%s' and t.DATA>(NOW() - INTERVAL 15 MINUTE)
        order by 1 desc limit 1;
        """
    que= sql % (name,orig,dest)
    cnt = 0 # количество извлекаемых записей из БД
    try:
        if db!="" :
		    # Execute the SQL command
            cursor.execute(que)
            # Fetch a single row using fetchone() method.
            data = cursor.fetchone()
            cnt = cursor.rowcount ;
    except:
        print "Error: unable to fetch data."
        #return(-21)
    ## формат=Источник1, дата на которую установлен курс, 1EUR = xxRUB
    if (cnt>0) : # берем значения из БД
        print "DB = % 20s, %20s, 1%s=%s %s" % (data[1], data[2], data[3], data[5], data[4] )
    if (cnt<=0) : # загружаем из Интернета
        # Парсим файлы данных
        (dname,ddate,drate) = XMLParcerDB( url , orig, dest )
        #print dname,ddate,drate
        # Вносим значения в базу - если они есть
        if (drate!="-1" and db!="") : # вносим значения в базу
            # подготавливаем дату к формату DATETIME
            dtobj = datetime.datetime.strptime(ddate, "%Y-%m-%d %H:%M:%S")
			# Prepare SQL query to INSERT a record into the database.
            sql = "INSERT INTO t (SRC, DATA, ORIG, DEST, VALUE) \
                   VALUES ('%s', '%s', '%s', '%s', '%s' )" % \
                  (dname, dtobj, orig, dest, drate)
            try:
                # Execute the SQL command
                cursor.execute(sql)
                # Commit your changes in the database
                db.commit()
            except:
                # Rollback in case there is any error
                db.rollback()
        if (drate!="-1") :
            print "-- = % 20s, %20s, 1%s=%s %s" % (dname, ddate, orig, drate, dest )
        else :
            print "-- = % 20s, %20s, 1%s=---- %s" % (dname, ddate, orig, dest )
    # disconnect from server
    if db!="" : db.close()
    #===================================================
    return(0)


def Main():
    """Главная функция"""
    #===================================================
    now_date = datetime.date.today() # Текущая дата (без времени)
    now_time = datetime.datetime.now() # Текущая дата со временем
    smsg = "Script time run= " + now_time.strftime("%Y-%m-%d %H:%M:%S")
    print (smsg)
    print ""
    #===================================================
    # 0 - выбираем аргументы командной строки
    #===================================================
    parser = createParser()
    args = parser.parse_args(sys.argv[1:])
    orig = ''
    if args.orig : orig = format (args.orig)
    dest = ''
    if args.dest : dest = format (args.dest)
    if dest=='' or orig=='' :
        print "Error - no set parameters. Script - break."
        return (-1)
    d1=dest.replace("'","")
    o1=orig.replace("'","")
    (orig,dest)=(o1,d1)
    #===================================================
    # 1 - запускаем потоки-события
    #===================================================
    ### запуск без потоков
    #for name, url in urls.items(): MainSQLXml(name, url, orig, dest)
	###
    jobs = [gevent.spawn(MainSQLXml, name, url, orig, dest) for name, url in urls.items()]
    gevent.joinall(jobs)
    #===================================================
    return(0)


if __name__ == '__main__':
    Main()



