#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov 21 12:24:43 2020

@author: vladb
"""

import subprocess
import numpy as np
import matplotlib.pyplot as plt;
import re

maxNumPages = 16384
numPages = 1
trials = 1000000

arrayNumPages = np.zeros(round(np.log(maxNumPages) / np.log(2)))
arrayTime = np.zeros(round(np.log(maxNumPages) / np.log(2)))

count = 0
        
while numPages < maxNumPages:
    proc = subprocess.Popen(['./tlb', f'{numPages}', f'{trials}'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    output = proc.communicate()[0]
    
    matchObj = re.search( rb'(?<=access: )(\d+(.\d*)?)', output, re.M|re.I)
    print(matchObj.group())
    timeNS = float(matchObj.group())

    arrayNumPages[count] = numPages
    arrayTime[count] = timeNS

    count = count + 1
    numPages = numPages * 2
        
plt.plot(arrayNumPages, arrayTime, 'o-')
plt.ylabel('Time per page access in ns')
plt.xlabel('Number of pages')
plt.savefig('page_access.png')
plt.show()