#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov  7 15:44:30 2020

@author: vladb
"""
#display out put line by line
import subprocess
import numpy as np
import matplotlib.pyplot as plt;

fractions = np.zeros(10)
limits = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
n = 100

for seed in range(6):
    count = 0
    for limit in limits:
        s = int(seed)
        proc = subprocess.Popen(['python', 'relocation.py', f'-s {s}', f'-l {limit}', f'-n {n}', '-c'], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        output = proc.communicate()[0]
        output = str(output)
        valids = output.count('VALID')
        fractions[count] += ((valids / n) / 6)
        count += 1
        
plt.plot(limits, fractions)
plt.ylabel('Fraction')
plt.xlabel('Limit')
plt.show()
