#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov 28 12:49:05 2020

@author: vladb
"""

import matplotlib.pyplot as plt;
import numpy as np

loops = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

loopTime1000 = [877.15, 233.81, 225.29, 227.07, 227.98, 236.02, 222.92, 224.15, 232.75, 224.73, 234.75]
loopBandWidth1000 = [1140.05, 4276.90, 4438.76, 4403.89, 4386.35, 4236.89, 4485.81, 4461.22, 4296.42, 4449.82, 4259.81]

loopTime3000 = [12063.20, 46904.24, 44353.43, 45090.48, 44183.05, 44751.04, 47400.83, 44539.24, 44624.18, 42557.00, 43569.75]
loopBandWidth3000 = [248.69, 63.96, 67.64, 66.53, 67.90, 67.04, 63.29, 67.36, 67.23, 70.49, 68.86]

loopTime1000 = np.asarray(loopTime1000, dtype=np.float32) / 1000
loopTime3000 = np.asarray(loopTime3000, dtype=np.float32) / 1000

print(np.mean(loopBandWidth1000))
print(np.mean(loopBandWidth3000))

memory = [500, 1000, 1500, 2000, 2500, 3000]
bandwidthAverage = [3928.77, 4075.99, 4013.38, 227.75, 90.96, 83.54]

plt.plot(loops, loopTime1000, 'o-', color='green')
plt.plot(loops, loopTime3000, 'o-', color='red')
plt.ylabel('Finish time in ms')
plt.xlabel('Loops')
plt.title('Finish times of loops')
plt.yticks(range(0, 50, 5))
plt.legend(('./mem 1000', './mem 3000'),loc='center right')
plt.show()

plt.plot(loops, loopBandWidth1000, 'o-', color='green')
plt.plot(loops, loopBandWidth3000, 'o-', color='red')
plt.ylabel('Bandwidth (MB/s)')
plt.xlabel('Loops')
plt.title('Performance ./mem 1000 vs 3000')
plt.yticks(range(0, 4500, 500))
plt.legend(('./mem 1000', './mem 3000'),loc='center right')
plt.show()

plt.plot(memory, bandwidthAverage, 'o-', color='black')
plt.ylabel('Average bandwidth (MB/s)')
plt.xlabel('Memory (MB)')
plt.show()