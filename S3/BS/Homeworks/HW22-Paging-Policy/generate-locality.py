#!/usr/bin/env python3

# Implements the 80-20 Workload

import random

random.seed(14)

numaddrs = 10
maxpage = 10

addrList = []
hotPages = []
coldPages = []
allPages = [0,1,2,3,4,5,6,7,8,9]

random.shuffle(allPages)
hotPages = allPages[:2]
coldPages = allPages[2:]    

for i in range(8):
    addrList.append(random.choice(hotPages))
    
for i in range(2):
    addrList.append(random.choice(coldPages))
    
random.shuffle(addrList)

print(addrList)
