# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

data, time = np.genfromtxt("decodedRichtig.csv", delimiter=",", unpack=True, skip_header=0)

plt.title('Keyboard Ton C4')
plt.xlabel('Time [ms]')
plt.ylabel('Amplitude [Digital Number]')

plt.minorticks_on()
plt.grid(which='major', linestyle='-', linewidth='0.5', color='black')
plt.grid(which='minor', linestyle=':', linewidth='0.5', color='gray')

plt.plot(time[100000:100300], data[100000:100300],  "-")
plt.savefig('Keyboard.png', dpi=900)
plt.show()

#Abgelesen von Plot:
#Eine Schwingung geht von 2296 1,5 bis 2298 1,5
#Grundperiode => 2ms
#Grundfrequenz => 500Hz

print("Grundperiode: 2ms")
print("Grundfrequenz: 500Hz")

#kann auch durch Abtastintervall * Signallänge berechnet werden
gemesseneZeit = 5.17184853553772 #sekunden

NOFFRAMES = 220
FRAMESIZE = 1024

abtastintervall = (gemesseneZeit / (NOFFRAMES*FRAMESIZE))
signaldauer = gemesseneZeit
signallaenge = NOFFRAMES*FRAMESIZE
abtastfrequenz = 1/(abtastintervall)

print("Signaldauer: " + str(signaldauer) + "sec")
print("Abtastfrequenz: " + str(abtastfrequenz) + "Hz")
print("Signallänge (Anzahl Abtastzeitpunkte): " + str(signallaenge))
print("Abtastintervall: " + str(abtastintervall) + "sec")