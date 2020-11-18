import numpy as np
import matplotlib.pyplot as p;
import glob
from natsort import natsorted

# AUFGABE 1

# Dateien werden geladen und nach dem Namen sortiert.
allFiles = glob.glob("/Users/vladb/Git/htwg/S3/SSS/Versuch 1/messwerte/*.csv")
allFiles = natsorted(allFiles)

# Die Arrays fuer die Spannungen, Standardabweichung und Distanzen werden erstellt
arrayMean = np.zeros(20)
arrayStd = np.zeros(20)
arrayDistance = [100,130,160,190,220,250,280,310,330,360,390,420,450,480,510,540,570,600,630,660]

# Index fuer Arrays Traversierung
index = 0
    
print("Mittelwert und Standardabweichung der einzelnen Dateien")

# Es werden alle Dateien jeweils verarbeitet
for filePath in allFiles:
    # Spalten trennen. Die Werte der DSpannungen befinden sich in der fuenften Spalte
    # Die ersten 1000 Werte werden weggelassen.
    inputData = np.genfromtxt(filePath, delimiter = ',')
    voltage = inputData[1000:, 4]
    
    # Hier wird die der Spannungsmittelwert und Standardabweichung anhand der Stichproben berechnet
    arrayStd[index] = np.std(voltage)
    arrayMean[index] = voltage.mean()
    print("Datei: m%2d, Mittelwert: %.3f, Standardabweichung: %.5f" % (index+1, 
                                                                       arrayMean[index],
                                                                       arrayStd[index]))
    index = index + 1

print("")

# Zusammenhang zwischen Durchschnittsspannung und Distanz
p.plot(arrayMean, arrayDistance)
p.ylabel('Distance [mm]')
p.xlabel('Voltage [V]')
p.show()

# Zusammenhand zwischen Distanz und Standardabweichung
p.plot(arrayDistance, arrayStd)
p.title("Standard deviation")
p.ylabel("Voltage [V]")
p.xlabel("Distance [mm]")
p.show()