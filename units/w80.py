#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------------
import os
import time
import datetime
import threading
import string
import re

ss = 'Foreign Currency Market http://www.cbr.ru/scripts/XML_daily.asp European Central Bank  http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml'

res = []

def to_utf8(string):
    try:
        return string.decode('utf8')
    except UnicodeEncodeError:
        return string

def split_strings(text):
    text = to_utf8(text)
    if len(text)>80:
        i = text.rfind(' ',0,79)
        if i != -1:
            res.append(text[:i]+'\n')
            split_strings(text[i+1:])
    else :
        res.append(text+'')

def Main():
    """Главная функция"""
    print ss
    split_strings(ss)
    print res
    pass
    sr=''.join(res)
    print sr
    pass
    return(0)


if __name__ == '__main__':
    Main()



