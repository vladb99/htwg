# -*- coding: utf-8 -*-
"""
Created on Sat Jan  2 16:57:34 2021

@author: danie
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

def calcSpectrum(data):
    anzahlAbschnitte = 170
    laengeAbschnitt = 512
    breiteUeberlappung = int(laengeAbschnitt / 2)
    
    signallaenge = anzahlAbschnitte * breiteUeberlappung
    
    window = np.ndarray(shape=(anzahlAbschnitte,signallaenge))
    gaussianwindow = signal.gaussian(laengeAbschnitt, std=512/4)
    
    for y in range(0, anzahlAbschnitte - 1):
        temp = np.zeros(signallaenge)
        von = int(y * breiteUeberlappung)
        bis = int(von + laengeAbschnitt)
        #print(y)
        temp[0:von] = np.zeros(von)
        temp[von:bis] = data[von:bis] * gaussianwindow
        temp[bis:signallaenge] = np.zeros(signallaenge - bis)
        
        window[y] = np.abs(np.fft.fft(temp))
        
    
    meanWindow = np.zeros(signallaenge)
    
    for y in range(0, signallaenge):
        summe = 0
        for x in range(0, anzahlAbschnitte):
            summe = summe + window[x,y]
            
        meanWindow[y] = summe / anzahlAbschnitte
        
    return meanWindow

hoch = np.genfromtxt('hoch1.csv', delimiter=",", unpack=True, skip_header=0)
tief = np.genfromtxt('tief1.csv', delimiter=",", unpack=True, skip_header=0)
links = np.genfromtxt('links1.csv', delimiter=",", unpack=True, skip_header=0)
rechts = np.genfromtxt('rechts1.csv', delimiter=",", unpack=True, skip_header=0)


hochSpec = calcSpectrum(hoch)
tiefSpec = calcSpectrum(tief)
linksSpec = calcSpectrum(links)
rechtsSpec = calcSpectrum(rechts)

signallaenge = 43520
abtastintervall = 0.022957424252209337 / 1000 #sec
haelfte = int(signallaenge / 2)
freq = np.zeros(signallaenge)
# Formel um die Anzahl der Schwingungen in die Freuquenz umzurechnen - f = n / (M * Δt)
for n in range(0, signallaenge, 1):
    freq[n] = n/(abtastintervall * signallaenge)

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], hochSpec[:haelfte], "-")
plt.grid()
plt.title('Erste Aufnahme "Hoch"')
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('ersteAufnahmeHoch.png')
plt.show()

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], tiefSpec[:haelfte], "-")
plt.grid()
plt.title('Erste Aufnahme "Tief"')
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('ersteAufnahmeTief.png')
plt.show()

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], linksSpec[:haelfte], "-")
plt.grid()
plt.title('Erste Aufnahme "Links"')
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('ersteAufnahmeLinks.png')
plt.show()

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], rechtsSpec[:haelfte], "-")
plt.grid()
plt.title('Erste Aufnahme "Rechts"')
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('ersteAufnahmeRechts.png')
plt.show()