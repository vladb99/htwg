# -*- coding: utf-8 -*-
"""
Created on Fri Jan 15 12:17:10 2021

@author: danie
"""

import math

uAd = [1.0166, 2.07, 3.076, 4.082, 5, 6.006, 7.041, 8.047, 8.965, 9.99]
uPm = [1.022, 2.07, 3.071, 4.07, 4.98, 5.98, 7.04, 8.04, 8.95, 10.034]
uRef = [1.027, 2.079, 3.084, 4.09, 5, 6.007, 7.061, 8.068, 8.979, 10.034]

index = [0,1,2,3,4,5,6,7,8,9]

sAd = 0
sPm = 0

n = 10

for i in index:
    sAd = sAd + math.pow((uRef[i] - uAd[i]), 2)
    sPm = sPm + math.pow((uRef[i] - uPm[i]), 2)
    
sAd = math.sqrt(1/(n-1) * sAd)
sPm = math.sqrt(1/(n-1) * sPm)

print(sAd)
print(sPm)