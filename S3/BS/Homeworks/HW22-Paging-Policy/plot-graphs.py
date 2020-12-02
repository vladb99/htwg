 #!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@author: vladb
"""

import matplotlib.pyplot as plt;

cacheSize = [1, 2, 3, 4, 5]

fifoHR = [49.39, 78.91, 88.54, 91.59, 93.92]
lruHR = [49.39, 84.77, 89.91, 93.66, 95.36]
randHR = [49.39, 78.34, 86.79, 91.08, 93.59]
clockHR = [49.39, 80.31, 88.40, 92.44, 94.70]
mruHR = [49.39, 49.50, 50.67, 50.78, 50.91]
optHR = [50.43, 86.48, 94.49, 96.51, 97.40] # mit 150000 elemente weil sonst zu lange gedauert



plt.plot(cacheSize, fifoHR, 'o-', color='green')
plt.plot(cacheSize, lruHR, 'o-', color='red')
plt.plot(cacheSize, randHR, 'o-', color='blue')
plt.plot(cacheSize, clockHR, 'o-', color='brown')
plt.plot(cacheSize, mruHR, 'o-', color='purple')
plt.plot(cacheSize, optHR, 'o-', color='yellow')
plt.ylabel('Cache size')
plt.xlabel('Hit rate')
#plt.yticks(range(0, 50, 5))
plt.legend(('FIFO', 'LRU', 'RAND', 'CLOCK', 'MRU', 'OPT'),loc='lower right')
plt.show()
