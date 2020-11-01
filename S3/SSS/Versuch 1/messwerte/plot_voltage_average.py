# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as p;
import glob
from natsort import natsorted
import math

# Einlesen Mittelwert und Standardabweichung AUFGABE 2

allFiles = glob.glob("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/*.csv")
allFiles = natsorted(allFiles)

arrayMean = np.zeros(20)
arrayStd = np.zeros(20)
arrayMeanFluct = np.zeros(20)
arrayDistance = [100,130,160,190,220,250,280,310,330,360,390,420,450,480,510,540,570,600,630,660]

index = 0
    
print("Mittelwert und Standardabweichung der einzelnen Dateien")
for filePath in allFiles:
    inputData = np.genfromtxt(filePath, delimiter = ',')
    voltage = inputData[1000:, 4]
    #fluctuationVoltage = inputData[1100:, 3]
    arrayStd[index] = np.std(voltage)
    arrayMean[index] = voltage.mean()
    #print(fluctuationVoltage.mean() * 1000)
    print("Datei: m%2d, Mittelwert: %.3f, Standardabweichung: %.5f" % (index+1, 
                                                                       arrayMean[index],
                                                                       arrayStd[index]))
    index = index + 1

print("")
fig, axes = p.subplots(nrows=2, ncols=2)
axes[0, 0].plot(arrayMean, arrayDistance)
axes[0, 0].set_title("Average")
axes[0, 0].set_xlabel("Voltage [V]")
axes[0, 0].set_ylabel("Disctance [mm]")
axes[0, 1].plot(arrayDistance, arrayStd)
axes[0, 1].set_title("Standard deviation")
axes[0, 1].set_ylabel("Voltage [V]")
axes[0, 1].set_xlabel("Disctance [mm]")
fig.tight_layout()

#Linear regression AUFGABE 2

logVoltage = np.log(arrayMean)
logDistance = np.log(arrayDistance)

meanLogVoltage = logVoltage.mean()
meanLogDistance = logDistance.mean()

a1 = 0
a2 = 0
for i in range(len(logVoltage)):
    a1 += (logVoltage[i] - meanLogVoltage) * (logDistance[i] - meanLogDistance)
    a2 += pow((logVoltage[i] - meanLogVoltage), 2) #Spannung als x
    
a = a1 / a2
b = meanLogDistance - a * meanLogVoltage

print("Variablen für Lineare Regression")
print("a: %f" % (a))
print("b: %f" % (b))
print("")

axes[1, 0].plot([a * x for x in logVoltage], logVoltage)
axes[1, 0].set_title("ln y = a * ln x")
axes[1, 0].set_xlabel("Distance [mm]")
axes[1, 0].set_ylabel("Voltage [V]")

axes[1, 1].plot(arrayMean, [np.exp(a * x + b) for x in logVoltage])
axes[1, 1].set_title("y = exp(a · ln x + b)")
axes[1, 1].set_ylabel("Distance [mm]")
axes[1, 1].set_xlabel("Voltage [V]")


# Flächenmessung AUFGABE 3a)

fileWidth = open("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/Blatt Messungen/dina4b.csv")
fileLength = open("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/Blatt Messungen/dina4l.csv")

voltageWidth = np.genfromtxt(fileWidth , delimiter= ",", skip_header=1000, usecols = (4))
voltageLength = np.genfromtxt(fileLength , delimiter= ",", skip_header=1000, usecols = (4))

# Width
sizeWidth = voltageWidth.shape[0]
meanWidth = voltageWidth.mean()
stdWidth = np.std(voltageWidth)

delta68W = stdWidth / math.sqrt(sizeWidth)

interval68W = [meanWidth - stdWidth, meanWidth + stdWidth]
interval95W = [meanWidth - 1.96 * stdWidth, meanWidth + 1.96 * stdWidth]


# Length
sizeLength = voltageLength.shape[0]
meanLength = voltageLength.mean()
stdLength = np.std(voltageLength)

delta68L = stdLength / math.sqrt(sizeLength)

interval68L = [meanLength - stdLength, meanLength + stdLength]
interval95L = [meanLength - 1.96 * stdLength, meanLength + 1.96 * stdLength]

print("Correction and intervals:")
print("WIDTH")
print("u = (%f +- %f)" % (meanWidth, delta68W))
print("68%% Interval: %f to %f" % (interval68W[0], interval68W[1]))
print("95%% Interval: %f to %f" % (interval95W[0], interval95W[1]))
print("")
print("LENGTH")
print("u = (%f +- %f)" % (meanLength, delta68L))
print("68%% Interval: %f to %f" % (interval68L[0], interval68L[1]))
print("95%% Interval: %f to %f" % (interval95L[0], interval95L[1]))
print("")

width = np.exp(a * np.log(meanWidth) + b)
print("Width: %.3f cm" % (width / 10))

#a*e^b*x^(a-1) 













