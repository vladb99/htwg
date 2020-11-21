#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov 21 12:24:43 2020

@author: vladb
"""
import sys
import subprocess
import numpy as np
import matplotlib.pyplot as plt;
import re
import argparse

parser = argparse.ArgumentParser(description='Script so useful.')
parser.add_argument("--trials", type=int, default=10000)

args = parser.parse_args()

trials = args.trials

maxNumPages = 524288
numPages = 1

arrayNumPages = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
arrayTime = np.zeros(int(round(np.log(maxNumPages) / np.log(2))))

x = [1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131071,262144]

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
plt.xticks(x2, arrayNumPages, rotation=20, fontsize='x-small')
plt.ylabel('Time per page access in ns')
plt.xlabel('Number of pages')
plt.title('TLB Size Measurement (multiple cpu) ' + str(trials))
plt.savefig('page_access.png')
plt.show()