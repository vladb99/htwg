# -*- coding: utf-8 -*-

import cv2
import numpy as np

path = 'C:/Users/danie/Desktop/Versuch2/Weissbilder/'
  
arrayImages = [np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601)),np.zeros((401,601))]

#Einlesen der 10 Weissbilder
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
    
    arrayImages[n] = gray
    
whiteIntImage = np.zeros((401,601))

#Mittelwertbild berechnen
for n in range(10):
    for i in range(401):
        for j in range(601):
            whiteIntImage[i,j] = whiteIntImage[i,j] + (arrayImages[n][i,j] / 10)
            
#print('for loop done')

#Dunkelbild einlesen
blackIntImage = cv2.imread('C:/Users/danie/.spyder-py3/maxContrastBlackImage.png', cv2.IMREAD_GRAYSCALE)

#Mittelwertbild - Dunkelbild
whiteMinusBlackIntImage = np.zeros((401,601))
whiteMinusBlackIntImage = whiteIntImage - blackIntImage

#Weißbild konvertieren um es kontrastmaximiert dazustellen
convertedWhiteImage = whiteMinusBlackIntImage.astype(np.uint8)
maxContrastWhiteIntImage = cv2.equalizeHist(convertedWhiteImage)

#Speichern der Bilder
cv2.imwrite('maxContrastWhiteImage.png', maxContrastWhiteIntImage)
cv2.imwrite('whiteMinusBlackImage.png', convertedWhiteImage)
cv2.imwrite('meanWhiteImage.png', whiteIntImage)

#print('done')