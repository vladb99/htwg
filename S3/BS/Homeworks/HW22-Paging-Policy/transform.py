#!/usr/bin/env python3
# -*- coding: utf-8 -*-

refsFile = open('ref-trace.txt', 'r')
vpnFile = open('vpn.txt', 'w')

mask = 0xfffff000
shift = 12

for line in refsFile:
    if not line.startswith('='):
        va = int("0x" + line[3:11], 16)
        vpn = (va & mask) >> 12
        vpnFile.write(str(vpn) + "\n")

refsFile.close()
vpnFile.close()