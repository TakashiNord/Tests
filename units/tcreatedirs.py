#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------------
import os
import datetime
import string
from urlparse import urlparse


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


def Main():
    """Главная функция"""
    #===================================================
    #url='https://lenta.ru/news/2017/08/02/rosgvard/'
    url='https://www.gazeta.ru/social/2017/08/02/10815025.shtml'
    # 1 создавать пути, 0 - просто файл
    ret=CreateDirsFile( url , 1 )
    print ret
    return(0)


if __name__ == '__main__':
    Main()
