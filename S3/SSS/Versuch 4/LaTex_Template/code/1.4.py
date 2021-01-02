from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("rechts1.csv", delimiter=",", unpack=True, skip_header=0)

anzahlAbschnitte = 170
laengeAbschnitt = 512
breiteUeberlappung = int(laengeAbschnitt / 2)

signallaenge = anzahlAbschnitte * breiteUeberlappung

#window = np.zeros(anzahlAbschnitte * breiteUeberlappung)
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
    
# Darstellung des Amplitudenspektrums
plt.plot(gaussianwindow)
plt.grid(True)
plt.title('Gaußsche Fensterfunktion')
plt.xlabel('Samples')
plt.ylabel('Amplitude')
#plt.savefig('Gauss.png')
plt.show()

meanWindow = np.zeros(signallaenge)

for y in range(0, signallaenge):
    summe = 0
    for x in range(0, anzahlAbschnitte):
        summe = summe + window[x,y]
        
    meanWindow[y] = summe / anzahlAbschnitte


abtastintervall = 0.022957424252209337 / 1000 #sec
signallaenge = anzahlAbschnitte * breiteUeberlappung
haelfte = int(signallaenge / 2)
freq = np.zeros(signallaenge)

# Formel um die Anzahl der Schwingungen in die Freuquenz umzurechnen - f = n / (M * delta t)
for n in range(0, signallaenge, 1):
    freq[n] = n/(abtastintervall * signallaenge)

# Darstellung des Amplitudenspektrums
plt.plot(freq[:haelfte], meanWindow[:haelfte], "-")
plt.grid()
plt.title('Amplitudenspektrum "Hallo" mit Windowing')
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
#plt.savefig('AmplitudenspektrumBreitWindow.png')
plt.show()

# Darstellung des Amplitudenspektrums
plt.plot(freq[:2500], meanWindow[:2500], "-")
plt.title('Reingezoomtes Amplitudenspektrum "Hallo" mit Windowing')
plt.grid()
plt.xlabel('Frequency in Hz')
plt.ylabel('Amplitude [Digital Number]')
#plt.savefig('AmplitudenspektrumSchmalWindow.png')
plt.show()