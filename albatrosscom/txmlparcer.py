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
import os
import random
import hashlib
import shutil
import urllib2
#from urllib import urlopen
import xml.etree.ElementTree as ET


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


def Main():
    """Главная функция"""
    #===================================================
    url='http://www.cbr.ru/scripts/XML_daily.asp'
    #url='http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml'
    orig='EUR'
    dest='RUB'
    ret=XMLParcerDB( url , orig, dest )
    print ret[0] , ret[1] , ret[2]
    return(0)


if __name__ == '__main__':
    Main()



