import pyaudio
import numpy as np
import matplotlib.pyplot as plt
FORMAT = pyaudio.paInt16
SAMPLEFREQ = 44100
FRAMESIZE = 1024
NOFFRAMES = 220

p = pyaudio.PyAudio()
print("running")
stream = p.open(format=FORMAT,channels=1,rate=SAMPLEFREQ,input=True,frames_per_buffer=FRAMESIZE)
data = stream.read(NOFFRAMES*FRAMESIZE)
decoded = np.fromstring(data, 'Int16') / ((2**15)/2-1)
stream.stop_stream()
stream.close()
p.terminate()

# Triggerfunktion schneidet bis Schwellenwert alles ab
start = np.argmax(np.abs(decoded) > 0.2)
# Berechnung Endwert der Aufnahme
end = start + 44100 #abtastintervall * 44100 ergibt 1 sec
triggered = decoded[start:end]
#0er anhängen wenn nötig
triggered = np.concatenate((triggered, [0]*(44100 - end - start)))
np.savetxt("rechts5_training.csv", triggered, delimiter=",")

plt.plot(triggered)
plt.title('Aufnahme von "Hallo" Getriggert')
plt.xlabel('Time')
plt.ylabel('Amplitude [Digital Number]')
#plt.savefig('AufnahmeHalloGetriggert.png')
plt.show()

plt.plot(decoded)
plt.title('Aufnahme von "Hallo" Original')
plt.xlabel('Time')
plt.ylabel('Amplitude [Digital Number]')
#plt.savefig('AufnahmeHalloOriginal.png')
plt.show()