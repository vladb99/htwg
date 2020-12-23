 #!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt;

numOfThreads = [1, 2, 3, 4, 5, 6, 7, 8]
avgTimeToCount = [1.81, 3.55, 5.35, 7.17, 9.01, 10.69, 12.65, 14.71] # in ms

thresholds = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]

plt.plot(numOfThreads, avgTimeToCount, 'o-', color='green')
plt.xlabel('Threads')
plt.ylabel('Time in ms')
plt.title('Count to 1.000.000 per thread')
plt.show()
