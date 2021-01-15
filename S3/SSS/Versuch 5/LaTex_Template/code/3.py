# -*- coding: utf-8 -*-
"""
Created on Fri Jan 15 13:20:43 2021

@author: danie
"""

import math

uAd = [0.566, 1.072, 1.578, 2.096, 2.609, 3.121, 3.634, 4.139, 4.635, 5.127]
uRef = [0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5]

index = [0,1,2,3,4,5,6,7,8, 9]

sAd = 0

n = 10

for i in index:
    sAd = sAd + math.pow((uRef[i] - uAd[i]), 2)
    
sAd = math.sqrt(1/(n-1) * sAd)

print(sAd)