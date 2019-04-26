#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------------
import os
import time
import datetime
import threading
import string
import re

ss = """
    'Foreign Currency Market http://www.cbr.ru/scripts/XML_daily.asp',
    'European Central Bank  http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml'
"""

def Main():
    """Главная функция"""
    res = []
    rows = ss.splitlines()
    print ss
    s_ostatok=""
    for row in rows:
        if row:
            s=""
            if len(s_ostatok>0):
                row.join(s_ostatok)
            for item in row
                li=len(item)
                lo=len(s)
                l=lo+li
                if l<80 :
                    s.join(item)
                else :
                    s_ostatok.join(item)
        res.append(s)    
    print res
    pass
    return(0)


if __name__ == '__main__':
    Main()



