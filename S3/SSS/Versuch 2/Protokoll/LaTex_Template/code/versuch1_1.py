# -*- coding: utf-8 -*-

import cv2
import numpy as np
import matplotlib.pyplot as plt

path = r'C:\Users\danie\Desktop\Versuch2\Grauwertkeil\1.png'
  
img = cv2.imread(path) 

#Bild von Originalgröße 6000x4000 runterskalieren damit es auf dem Monitor angezeigt werden kann
scale_percent = 10 # wird auf 10% der Originalgröße skaliert
width = int(img.shape[1] * scale_percent / 100)
height = int(img.shape[0] * scale_percent / 100)
dim = (width, height)
resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
 
#in Grauwertbild umwandeln
gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)

#Das neue Bild ist jetzt 601x401 
print('Resized Dimensions : ',resized.shape)

#Speichern des resized Grauwert und des resized Original Bildes
filename = 'Grauwertkeil.png'
cv2.imwrite(filename, gray)
filename = 'Original.png'
cv2.imwrite(filename, resized)

#Bereiche aus dem Gesamtbild extrahieren
cropGray1 = gray[0:400, 0:100]
cropGray2 = gray[0:400, 107:227]
cropGray3 = gray[0:400, 234:355]
cropGray4 = gray[0:400, 362:483]
cropGray5 = gray[0:400, 490:600]

#Einzelne Bereiche abspeichern
filename = 'cropGray1.png'
cv2.imwrite(filename, cropGray1)
filename = 'cropGray2.png'
cv2.imwrite(filename, cropGray2)
filename = 'cropGray3.png'
cv2.imwrite(filename, cropGray3)
filename = 'cropGray4.png'
cv2.imwrite(filename, cropGray4)
filename = 'cropGray5.png'
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