# -*- coding: utf-8 -*-
"""
Created on Mon Nov 23 15:11:51 2020

@author: danie
"""
import cv2
import numpy as np

path = 'C:/Users/danie/Desktop/Versuch2/Schwarzbilder/'
  
arrayImages = [np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601))]

for n in range(10):
    pathToFile = path + str(n + 1) + '.png'
    img = cv2.imread(pathToFile) 
    
    #Bild von Originalgröße 6000x4000 runterskalieren damit es auf dem Monitor angezeigt werden kann
    scale_percent = 10 # wird auf 10% der Originalgröße skaliert
    width = int(img.shape[1] * scale_percent / 100)
    height = int(img.shape[0] * scale_percent / 100)
    dim = (width, height)
    resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
    
    #eingelesenes Bild in Grauwertbild umwandeln
    gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
    
    #Von int Image in float Image convertieren
    info = np.iinfo(gray.dtype)
    arrayImages[n] = gray.astype(np.float64) / info.max
    
blackFloatImage = np.zeros((401,601))
    
for n in range(10):
    for i in range(401):
        for j in range(601):
            blackFloatImage[i,j] = blackFloatImage[i,j] + (arrayImages[n][i,j] / 10)
            
#Von float Image in int Image convertieren
blackFloatImage = blackFloatImage * 255
blackIntImage = blackFloatImage.astype(np.uint8)

maxContrastBlackIntImage = cv2.equalizeHist(blackIntImage)

#Speichern des Kontrastmaximiertes Dunkelbilds
cv2.imwrite('maxContrastBlackImage.png', maxContrastBlackIntImage)

#cv2.imshow('image',maxContrastBlackIntImage)
#cv2.waitKey(0)
#cv2.destroyAllWindows()

#Grauwertbild einlesen
grayIntImage = cv2.imread('Grauwertkeil.png')

#Convertieren in Graubild
grayIntImage = cv2.cvtColor(grayIntImage, cv2.COLOR_BGR2GRAY)

#Kontrastmaximiertes Dunkelbild von Grauwertbild subtrahieren
subGrayIntImage = grayIntImage - maxContrastBlackIntImage

#Speichern des Graubilds wo das Dunkelbild abgezogen wurde
cv2.imwrite('subGrayIntImage.png', subGrayIntImage)





