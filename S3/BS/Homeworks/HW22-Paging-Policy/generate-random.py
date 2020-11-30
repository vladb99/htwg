#!/usr/bin/env python3

import random

random.seed(7)
numaddrs = 10
maxpage = 10
addrList = []

for i in range(numaddrs):
    n = int(maxpage * random.random())
    addrList.append(n)
    
print(addrList)