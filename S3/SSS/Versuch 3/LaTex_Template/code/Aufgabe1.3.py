# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

data, time = np.genfromtxt("decodedRichtig.csv", delimiter=",", unpack=True, skip_header=0)

abtastintervall = 0.022957424252209337 / 1000 #sec
signallaenge = 225280

data = data # / 1000 #von mV in V

fourier = np.fft.fft(data)

spektrum = np.abs(fourier)

haelfte = int(signallaenge / 2)

print(abtastintervall * signallaenge)

freq = np.zeros(signallaenge)

# Formel um die Anzahl der Schwingungen in die Freuquenz umzurechnen - f = n / (M * (delta)t)
for n in range(0, signallaenge, 1):
    freq[n] = n/(abtastintervall * signallaenge)

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], spektrum[:haelfte], "-")
plt.grid()
plt.title("Amplitudenspektrum")
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('AmplitudenspektrumBreit.png')
plt.show()

# Darstellung des Amplitudenspektrums
plt.plot(freq[:10000], spektrum[:10000], "-")
plt.title("Reingezoomtes Amplitudenspektrum")
plt.grid()
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('AmplitudenspektrumSchmal.png')
plt.show()

maxValue = 0
maxFreq = 0

for i in range(0, haelfte):
    if(maxValue < spektrum[i]):
        maxValue = spektrum[i]
        maxFreq = freq[i]
        
print("Maximalster Amplitudenausschlag", round(maxValue, 1))
print("Frequenz mit der größten Amplitude", maxFreq)