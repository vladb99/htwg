import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("hallotriggered.csv", delimiter=",", unpack=True, skip_header=0)

abtastintervall = 0.022957424252209337 / 1000 #sec
signallaenge = 44100

fourier = np.fft.fft(data)

spektrum = np.abs(fourier)

haelfte = int(signallaenge / 2)

print(abtastintervall * signallaenge)

freq = np.zeros(signallaenge)

# Formel um die Anzahl der Schwingungen in die Freuquenz umzurechnen - f = n / (M * delta t)
for n in range(0, signallaenge, 1):
    freq[n] = n/(abtastintervall * signallaenge)

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], spektrum[:haelfte], "-")
plt.grid()
plt.title('Amplitudenspektrum "Hallo"')
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('AmplitudenspektrumBreit.png')
plt.show()

# Darstellung des Amplitudenspektrums
plt.plot(freq[:2500], spektrum[:2500], "-")
plt.title('Reingezoomtes Amplitudenspektrum "Hallo"')
plt.grid()
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('AmplitudenspektrumSchmal.png')
plt.show()