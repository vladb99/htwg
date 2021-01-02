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


def main():
    signallaenge = 43520 #damit es genau passt mit den window bereichen
    
    data = [np.zeros(signallaenge),np.zeros(signallaenge),np.zeros(signallaenge),np.zeros(signallaenge),np.zeros(signallaenge)]
    
    typ = "rechts" #hoch, tief, links, rechts
    
    for n in range(5):
        pathToFile = typ + str(n + 1) + '.csv'
        data[n] = np.genfromtxt(pathToFile, delimiter=",", unpack=True, skip_header=0)
        
    specs = np.zeros((5,signallaenge))
    for n in range(5):
        specs[n] = calcSpectrum(data[n])
        
    mean = np.zeros(signallaenge)
    for n in range(signallaenge):
        for i in range(5):
            mean[n] = mean[n] + (specs[i][n] / 5)
            
    abtastintervall = 0.022957424252209337 / 1000 #sec
    haelfte = int(signallaenge / 2)
    freq = np.zeros(signallaenge)
    # Formel um die Anzahl der Schwingungen in die Freuquenz umzurechnen - f = n / (M * delta t)
    for n in range(0, signallaenge, 1):
        freq[n] = n/(abtastintervall * signallaenge)
    
    np.savetxt(typ + "Mean.csv", mean, delimiter=",")
    
    # Darstellung des Amplitudenspektrums
    plt.plot(freq[:haelfte], mean[:haelfte], "-")
    plt.grid()
    plt.title('Referenzspektrum "' + typ + '"')
    plt.xlabel('Frequency in Hz')
    plt.ylabel('Amplitude [Digital Number]')
    plt.savefig('Referenzspektrum' + typ + '.png')
    plt.show()
    
    
main()