import numpy as np
from scipy import stats

hochMean = np.genfromtxt('hochMean.csv', delimiter=",", unpack=True, skip_header=0)
tiefMean = np.genfromtxt('tiefMean.csv', delimiter=",", unpack=True, skip_header=0)
linksMean = np.genfromtxt('linksMean.csv', delimiter=",", unpack=True, skip_header=0)
rechtsMean = np.genfromtxt('rechtsMean.csv', delimiter=",", unpack=True, skip_header=0)

directory = "person1/"

commands = ["hoch", "tief", "links", "rechts"]
names = []
for c in commands:
    for n in range(1, 6):
        names.append(c + str(n) + "_training.csv")

for name in names:
    spec = np.genfromtxt(directory + name, delimiter=",", unpack=True, skip_header=0)
    spec = spec[:43520]
    spec = np.abs(np.fft.fft(spec))
    
    korr = np.zeros(4)

    korr[0] = stats.pearsonr(spec, hochMean)[0]
    korr[1] = stats.pearsonr(spec, tiefMean)[0]
    korr[2] = stats.pearsonr(spec, linksMean)[0]
    korr[3] = stats.pearsonr(spec, rechtsMean)[0]
    
    if(np.max(korr) == korr[0]):
        print("Lösung: " + name + " - Geschätzt: Hoch mit koeff.: " + str(korr[0]))
    elif(np.max(korr) == korr[1]):
        print("Lösung: " + name + " - Geschätzt: Tief mit koeff.: " + str(korr[1]))
    elif(np.max(korr) == korr[2]):
        print("Lösung: " + name + " - Geschätzt: Links mit koeff.: " + str(korr[2]))
    elif(np.max(korr) == korr[3]):
        print("Lösung: " + name + " - Geschätzt: Rechts mit koeff.: " + str(korr[3]))
