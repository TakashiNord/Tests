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
from urllib import urlopen
from urlparse import urlparse
from HTMLParser import HTMLParser

""" принудительная установка кодовой страницы и локали """
#reload(sys)
#sys.setdefaultencoding('utf-8')
#
#import locale
#sys.setdefaultencoding(locale.getpreferredencoding())


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


def checkOs():
    # This function only looks for Mac,Linux or Windows
    if sys.platform == "darwin":
        operating_system = "posix"
    # Check for Windows
    elif os.name == "nt":
        operating_system = "windows"
    # Check for Linux
    elif os.name == "posix":
        operating_system = "posix"
    else:
        operating_system = "windows"
    # Return our operating system
    return operating_system


def CreateDirsFile( url, sv ):
    """url - ссылка url, sv = {1-создавать директории, 0-не создавать}, возвращает имя файла"""
    o = urlparse(url)
    # scheme://netloc/path;parameters?query#fragment
    scheme=o.scheme
    netloc=o.netloc
    path=o.path
    domain = netloc.split(':')[0]
    #print("domain, path ", domain, path)
    # получаем имя посл файла.
    f=os.path.basename(path)
    if f=="" :
        # выделяем последнюю папку - если нет файла
        f=os.path.dirname(path).split('/')[-1]
        # удаляем её из пути
        path=path.rstrip(f+'/')
    else:
        path=os.path.dirname(path)
    # заменяем расширение на name_date.txt
    t1 = datetime.datetime.now()
    t2 = t1.strftime("%Y%m%d_%H%M%S")
    fnew = f.split('.')[0]
    fnew = fnew + "_" + t2 + ".txt"
    #print(fnew)
    # текущее положение
    p=os.path.normpath(os.getcwd()) + os.path.sep
    if sv==1 :
        # создаем директории
        p = p + domain + os.path.sep + path + os.path.sep
        p = os.path.normpath(p) + os.path.sep
        if not os.path.exists(os.path.dirname(p)):
            os.makedirs(os.path.dirname(p))
    # создаем имя файла и возращаем его
    #print p
    fret=p + fnew
    return(fret)


""" Класс для разбивки текста по 80 символов  """
class MySplit():
    def __init__(self):
        self.res = []

    def to_utf8(self,s):
        try:
            return s.decode('cp1251') # utf-8
        except UnicodeEncodeError:
            return s

    def split_strings(self,text):
        text = self.to_utf8(text)
        if len(text)>80:
            i = text.rfind(' ',0,79)
            if i != -1:
                self.res.append(text[:i]+'\n')
                self.split_strings(text[i+1:])
        else :
            self.res.append(text+'')

    def split(self,texts):
        self.split_strings(texts)
        return (self.res)


def PageParcerP( url ):
    """ Основной обработчик """
    #===================================
    print 'Starting %s' % url
    pass
    # проверка Os
    if checkOs()!="windows" :
        print "OS not Windows. Fail break."
        return(-1)
    pass
    # Добавляем заголовок.
    headers = {'User-Agent' : 'Mozilla 5.10'}
    request = urllib2.Request(url, None, headers)
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
    #
    source = response.read()
    print '%s \n%s bytes\n%r' % (url, len(source), source[:100])
    #
    # для отладки
    #filename1 = 'text.txt' # создаем файл для отладки os.tempname
    #filename2 = os.path.join(os.getcwd(), filename1)
    #
    # создаем директории в текущей папке, возвращаем имя файла
    filename2=CreateDirsFile(url, 1)
    #
    if os.path.exists(filename2)==True : os.remove(filename2)
    #
    # пишем полученный материал
    fo = open(filename2, 'w')
    fo.write(source)
    fo.close( )
    # перекодировка в другую кодовую страницу
    with io.open(filename2, "r", encoding=codepage) as my_file:
        data = my_file.read()
    # проводим первый разбор
    parser = MyHTMLParser()
    parser.feed(data)
    res=parser.res
    print res
    # переводим массив строк в 1 строку
    stemp=''.join(res)
    # делим по 80 симв
    sp = MySplit()
    res2=sp.split(stemp)
    #
    if os.path.exists(filename2)==True : os.remove(filename2)
    #
    # пишем полученный материал
    fo = open(filename2, 'w')
    for s in res2 :
        fo.write(s.encode('utf8')) # data.decode('utf-8')
    fo.close( )
    pass
    return(0)


def Main():
    """Главная функция"""
    #===================================================
    url='https://lenta.ru/news/2017/08/02/rosgvard/'
    #url='https://www.gazeta.ru/social/2017/08/02/10815025.shtml'
    ret=PageParcerP( url )
    return(0)


if __name__ == '__main__':
    Main()



