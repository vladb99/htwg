# -*- coding: utf-8 -*-

import cv2
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread('C:/Users/danie/.spyder-py3/finalImage.png', cv2.IMREAD_GRAYSCALE) 

#Bereiche aus dem Gesamtbild extrahieren
cropGray1 = img[0:400, 0:100]
cropGray2 = img[0:400, 107:227]
cropGray3 = img[0:400, 234:355]
cropGray4 = img[0:400, 362:483]
cropGray5 = img[0:400, 490:600]

#Einzelne Bereiche abspeichern
filename = 'cropGray1_final.png'
cv2.imwrite(filename, cropGray1)
filename = 'cropGray2_final.png'
cv2.imwrite(filename, cropGray2)
filename = 'cropGray3_final.png'
cv2.imwrite(filename, cropGray3)
filename = 'cropGray4_final.png'
cv2.imwrite(filename, cropGray4)
filename = 'cropGray5_final.png'
cv2.imwrite(filename, cropGray5)

arrayCropedImages = (cropGray1, cropGray2, cropGray3, cropGray4, cropGray5)
arrayMean = np.zeros(5)
arrayStd = np.zeros(5)

#Empirische Standardabweichung und Durchschnitt berechnen
for n in range(5):
    mean, std = cv2.meanStdDev(arrayCropedImages[n])
    arrayMean[n] = mean
    arrayStd[n] = std
    print(f"Gray {n + 1} mean: {mean}")
    print(f"Gray {n + 1} std: {std}\n")


arrayPlot = ['Gray1', 'Gray2', 'Gray3', 'Gray4', 'Gray5']

plt.plot(arrayPlot, arrayMean)
plt.title('Durchschnittlicher Grauwert')
plt.xlabel('Grauwertkeil')
plt.ylabel('Durchschnittswert')
plt.show()

plt.plot(arrayPlot, arrayStd)
plt.title('Standardabweichung')
plt.xlabel('Grauwertkeil')
plt.ylabel('Standardabweichung')
plt.show()