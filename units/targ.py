#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------------
import os
import time
import datetime
import threading
import string
# парсер командной строки
import sys
import argparse

#
def createParser ():
    parser = argparse.ArgumentParser()
    ## примерный список параметров ('-u', '--url', required=True, default='')
    parser.add_argument ('-u', '--url', default='')
    return parser


def Parser1 ():
    parser = createParser()
    args = parser.parse_args(sys.argv[1:])
    #print (args)
    url = ''
    if args.url or args.u :
        if args.url :
            url = format (args.url)
        else :
            url = format (args.u)
    #url=url.translate("'","")
    pv=url.replace("'","")
    print ("url=", pv )
    return(pv)

	
def Parser2 ():
    if(len(sys.argv) < 2):
        print(
            "Usage:"
            " python filename.py <Input-Url>\n")
        sys.exit(1)
    pv = sys.argv[1]
    url= pv.strip("'")
    print ("arg =%s" % pv ) 
    return(pv)


def Main():
    """Главная функция"""
    #===================================================
    now_date = datetime.date.today() # Текущая дата (без времени)
    now_time = datetime.datetime.now() # Текущая дата со временем
    cur_hour = now_time.hour # Час текущий
    cur_minute = now_time.minute # Минута текущая
    smsg = "Time run= " + now_time.strftime("%Y-%m-%d %H:%M:%S")
    #===================================================
    """  разбор аргументов """
    #===================================================
    #Parser1 ()
    Parser2 ()
    #===================================================
    return(0)


if __name__ == '__main__':
    Main()



