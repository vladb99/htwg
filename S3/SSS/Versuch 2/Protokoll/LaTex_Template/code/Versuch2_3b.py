# -*- coding: utf-8 -*-

import cv2
import numpy as np

#Einlesen des meanWhiteImages und des InputImages 
#Das InputImage ist das Bild welche durch Grauwertkeil - Dunkelbild berechnet wurde
inputImage = cv2.imread('C:/Users/danie/.spyder-py3/subGrayIntImage.png', cv2.IMREAD_GRAYSCALE)
meanWhiteImage = np.float32(cv2.imread('C:/Users/danie/.spyder-py3/meanWhiteImage.png', cv2.IMREAD_GRAYSCALE))

#Bild normalisieren => Mittelwert 1
meanOfMeanWhiteImage = np.mean(meanWhiteImage)
normalizedImage = meanWhiteImage/meanOfMeanWhiteImage

print(np.mean(normalizedImage))

#Das durch Abzug des Dunkelbildes korrigierte Eingangsbild wird
#durch das normierte Weißbild dividiert
finalImage = inputImage / normalizedImage

#Resultat abspeichern
cv2.imwrite('finalImage.png', finalImage)