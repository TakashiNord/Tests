#!/usr/bin/env python
# -*- coding: utf-8 -*-
# encoding: utf-8
#-------------------------------------------------------------------------------
import os
import io
import time
import datetime
import threading
import string
import re
import sys
import os
import urlparse
import urllib2
from HTMLParser import HTMLParser


reload(sys)
sys.setdefaultencoding('utf-8')
#
import locale
sys.setdefaultencoding(locale.getpreferredencoding())


# p title h1 h2 h3
""" Класс для разбора тегов получаемой страницы  """
class MyHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.recording = False
        self.res = []
        self.href = 0
        self.fl = 0
        self.links = ""

    def handle_starttag(self, tag, attrs):
        if tag == 'p':
            self.recording = True
        if tag == 'iframe':
            pass
        if tag == 'a':
            if self.recording == True :
                self.href=1
                # находим аттрибут адреса ссылки
                for attr in attrs:
                    if attr[0] == 'href':
                        self.links = attr[1]
        if (tag != 'p' and self.recording == True):
            self.fl = 1

    def handle_endtag(self, tag):
        if tag == 'p':
            self.recording = False
        if tag == 'iframe':
            pass
        if tag == 'a':
            if self.recording == True :
                self.href=0
        if (tag != 'p' and self.recording == True):
            self.fl = 0

    def handle_data(self, data):
        if self.recording:
            if self.href==1:
                self.res.append("["+data+"|"+self.links+"]")
            else :
                if self.fl!= 1:
                    self.res.append(data)


def PageParcerP( url ):
    """ Возвращаем значения """
    #===================================
    print 'Starting %s' % url
    # Добавляем заголовок.
    headers = {'User-Agent' : 'Mozilla 5.10'}
    request = urllib2.Request(url, None, headers)
    #request = requests.Session(headers=headers)
    connected = False
    for i in range(10):
        try:
            response = urllib2.urlopen(request)
            connected = True
            break
        except urllib2.URLError:
            time.sleep(2)
    if not connected:
        print "html or Internet connection is unavailable. Fail silently."
        #sys.exit(1)
        return(-2)
    # Выводим заголовки
    print response.headers
    #  {'Content-Type': 'text/html; charset=utf-8'}
    # проверка кодовой страницы
    codep=response.headers.get('Content-Type')
    print codep
    c1=codep.split(';')
    codepage="utf-8"
    print c1
    for c in c1 :
        sc=c.strip()
        if (sc.find("charset=")>=0) :
            if (sc.find("windows-1251")>=0):
                codepage="cp1251"
            if (sc.find("utf-8")>=0):
                codepage="utf-8"
    print codepage
    #return 0
    source = response.read()
    #source = unicode(source, 'cp1251') # cp1251  utf-8  source.decode('cp1251')
    print '%s \n%s bytes\n%r' % (url, len(source), source[:100])
    filename1 = 'text.txt' # создаем файл под случайным именем для отладки os.tempname
    # удалить временный файл
    filename2 = os.path.join(os.getcwd(), filename1)
    if os.path.exists(filename2)==True : os.remove(filename2)
    file_object = open(filename2, 'w')
    file_object.write(source)
    file_object.close( )
    with io.open(filename2, "r", encoding=codepage) as my_file:
        data = my_file.read()
    parser = MyHTMLParser()
    parser.feed(data)
    res=parser.res
    print res
    #parser.close()
    pass
    return(0)


def Main():
    """Главная функция"""
    #===================================================
    #url='https://lenta.ru/news/2017/08/02/rosgvard/'
    url='https://www.gazeta.ru/social/2017/08/02/10815025.shtml'
    ret=PageParcerP( url )
    return(0)


if __name__ == '__main__':
    Main()



