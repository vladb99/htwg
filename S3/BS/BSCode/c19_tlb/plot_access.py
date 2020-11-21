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
trials = 10000

arrayNumPages = [0,0,0,0,0,0,0,0,0,0,0,0,0,0]
arrayTime = np.zeros(int(round(np.log(maxNumPages) / np.log(2))))

x = [1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192]

count = 0
        
while numPages < maxNumPages:
    proc = subprocess.Popen(['./tlb', f'{numPages}', f'{trials}'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    output = proc.communicate()[0]
    
    matchObj = re.search( rb'(?<=access: )(\d+(.\d*)?)', output, re.M|re.I)
    print(str(numPages) + " : " + str(matchObj.group()))
    timeNS = float(matchObj.group())

    arrayNumPages[count] = numPages
    arrayTime[count] = timeNS

    count = count + 1
    numPages = numPages * 2
        
N = len(arrayNumPages)
x2 = np.arange(N)
    
plt.plot(x2, arrayTime, 'o-')
plt.xticks(x2, arrayNumPages, fontsize='x-small')
plt.ylabel('Time per page access in ns')
plt.xlabel('Number of pages')
plt.title('TLB Size Measurement (multiple cpu)')
plt.savefig('page_access.png')
plt.show()