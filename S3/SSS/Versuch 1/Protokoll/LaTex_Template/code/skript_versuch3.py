import numpy as np
import math
# Flächenmessung AUFGABE 3

#voltageWidthData = np.genfromtxt("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/dina4b.csv" , delimiter= ",")
#voltageLengthData = np.genfromtxt("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/dina4l.csv" , delimiter= ",")

#voltageWidth = voltageWidthData[1000:, 4]
#voltageLength = voltageLengthData[1000:, 4]

fileWidth = open("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/Blatt Messungen/dina4b.csv")
fileLength = open("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/Blatt Messungen/dina4l.csv")

voltageWidth = np.genfromtxt(fileWidth , delimiter= ",", skip_header=1000, usecols = (4))
voltageLength = np.genfromtxt(fileLength , delimiter= ",", skip_header=1000, usecols = (4))

# STD nicht im Protokol deshalb von Messungen berechnet!
# Width
sizeWidth = voltageWidth.shape[0]
meanWidth = 0.890 #von handschriftlichem Aufschrieb
stdWidth = np.std(voltageWidth)

interval68W = [meanWidth - stdWidth, meanWidth + stdWidth]
interval95W = [meanWidth - 1.96 * stdWidth, meanWidth + 1.96 * stdWidth]

# Length
sizeLength = voltageLength.shape[0]
meanLength = 0.693 #von handschriftlichem Aufschrieb
stdLength = np.std(voltageLength)

interval68L = [meanLength - stdLength, meanLength + stdLength]
interval95L = [meanLength - 1.96 * stdLength, meanLength + 1.96 * stdLength]

print("Correction and intervals:")
print("WIDTH")
print("68%% Interval: %f to %f" % (interval68W[0], interval68W[1]))
print("95%% Interval: %f to %f" % (interval95W[0], interval95W[1]))
print("")
print("LENGTH")
print("68%% Interval: %f to %f" % (interval68L[0], interval68L[1]))
print("95%% Interval: %f to %f" % (interval95L[0], interval95L[1]))
print("")

##############################################################################

#Wird für die Fehlerfortpflanzung benötigt
delta68W = stdWidth / math.sqrt(sizeWidth)
delta68L = stdLength / math.sqrt(sizeLength)

print("WIDTH")
print("delta 68 u = (%f +- %f)" % (meanWidth, delta68W))
print("LENGTH")
print("delta 68 u = (%f +- %f)" % (meanLength, delta68L))
print("")

delta95W = stdWidth * 1.96 / math.sqrt(sizeWidth)
delta95L = stdLength * 1.96 / math.sqrt(sizeLength)

print("WIDTH")
print("delta 95 u = (%f +- %f)" % (meanWidth, delta95W))
print("LENGTH")
print("delta 95 u = (%f +- %f)" % (meanLength, delta95L))
print("")

##############################################################################

#Aus Versuch 2
a = -1.915981
b = 5.157991

#Ableitung der Funktion => a*e^b*x^(a-1)

#Berechnung für Vertrauensbereich von 68%
width = np.exp(a * np.log(meanWidth) + b)
deltaWidth68 = a * np.exp(b) * math.pow(meanWidth, a - 1) * delta68W
deltaWidth68 = abs(deltaWidth68)

length = np.exp(a * np.log(meanLength) + b)
deltaLength68 = a * np.exp(b) * math.pow(meanLength, a - 1) * delta68L
deltaLength68 = abs(deltaLength68)

print("Correction:")
print("w = (%f +- %f) cm" % (width / 10, deltaWidth68 / 10))
print("l = (%f +- %f) cm" % (length / 10, deltaLength68 / 10))

deltaArea = math.sqrt(math.pow(length * deltaWidth68, 2) + math.pow(width * deltaLength68, 2))
print("area = (%f +- %f) cm^2" % (width * length / 100, deltaArea / 100))

##############################################################################

#Berechnung für Vertrauensbereich von 95%
width = np.exp(a * np.log(meanWidth) + b)
deltaWidth95 = a * np.exp(b) * math.pow(meanWidth, a - 1) * delta95W
deltaWidth95 = abs(deltaWidth95)

length = np.exp(a * np.log(meanLength) + b)
deltaLength95 = a * np.exp(b) * math.pow(meanLength, a - 1) * delta95L
deltaLength95 = abs(deltaLength95)

print("Correction:")
print("w = (%f +- %f) cm" % (width / 10, deltaWidth95 / 10))
print("l = (%f +- %f) cm" % (length / 10, deltaLength95 / 10))

deltaArea = math.sqrt(math.pow(length * deltaWidth95, 2) + math.pow(width * deltaLength95, 2))
print("area = (%f +- %f) cm^2" % (width * length / 100, deltaArea / 100))