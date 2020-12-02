# -*- coding: utf-8 -*-

import cv2

whiteImage = cv2.imread('C:/Users/danie/.spyder-py3/meanWhiteImage.png')
blackImage = cv2.imread('C:/Users/danie/.spyder-py3/maxContrastBlackImage.png')

whiteImageGray = cv2.imread('C:/Users/danie/.spyder-py3/meanWhiteImage.png', cv2.IMREAD_GRAYSCALE)
blackImageGray = cv2.imread('C:/Users/danie/.spyder-py3/maxContrastBlackImage.png', cv2.IMREAD_GRAYSCALE)

black_highestValue = 0
black_lowestValue = 255

black_circleX_1 = 0
black_circleY_1 = 0
black_circleX_2 = 0
black_circleY_2 = 0

#Dunkelbild auf Stuck und Hot Pixel untersuchen
for i in range(401):
    for j in range(601):
        currentPixel = blackImageGray[i,j]
        
        if(currentPixel > black_highestValue):
            black_highestValue = currentPixel
            black_circleX_1 = i
            black_circleY_1 = j
            
        if(currentPixel < black_lowestValue):
            black_lowestValue = currentPixel
            black_circleX_2 = i
            black_circleY_2 = j
            
print("Höchster Wert im Dunkelbild: " + str(black_highestValue))
print("Niedrigster Wert im Dunkelbild: " + str(black_lowestValue))

circleBlackImage = blackImage
cv2.circle(circleBlackImage, (black_circleX_1, black_circleY_1), 4, (0,255,0), 2)#grüner Kis
cv2.circle(circleBlackImage, (black_circleX_2, black_circleY_2), 4, (0,0,255), 2)#roter Kreis

cv2.imwrite('circleBlackImage.png', circleBlackImage)

#-----------------------------------------------------------------------------

white_highestValue = 0
white_lowestValue = 255

white_circleX_1 = 0
white_circleY_1 = 0
white_circleX_2 = 0
white_circleY_2 = 0

#Weißbild auf Dead Pixel untersuchen
for i in range(401):
    for j in range(601):
        currentPixel = whiteImageGray[i,j]
        
        if(currentPixel > white_highestValue):
            white_highestValue = currentPixel
            white_circleX_1 = j
            white_circleY_1 = i
        
        if(currentPixel < white_lowestValue):
            white_lowestValue = currentPixel
            white_circleX_2 = j
            white_circleY_2 = i
            
print("Höchster Wert im Weißbild: " + str(white_highestValue))
print("Niedrigster Wert im Weißbild: " + str(white_lowestValue))
color = [0, 0, 255]
circleWhiteImage = whiteImage
cv2.circle(circleWhiteImage, (white_circleX_1, white_circleY_1), 4, (0,255,0), 2)#grüner Kreis
cv2.circle(circleWhiteImage, (white_circleX_2, white_circleY_2), 4, (0,0,255), 2)#roter Kreis

cv2.imwrite('circleWhiteImage.png', circleWhiteImage)