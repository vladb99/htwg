import time
import pyaudio
import numpy
import matplotlib.pyplot as plt
FORMAT = pyaudio.paInt16
SAMPLEFREQ = 44100
FRAMESIZE = 1024
NOFFRAMES = 220

start = time.time()

p = pyaudio.PyAudio()
print("running")
stream = p.open(format=FORMAT,channels=1,rate=SAMPLEFREQ,input=True,frames_per_buffer=FRAMESIZE)
data = stream.read(NOFFRAMES*FRAMESIZE)
decoded = numpy.fromstring(data, "Int16");
stream.stop_stream()
stream.close()
p.terminate()

end = time.time()

abtastintervall = ((end - start) * 1000) / (NOFFRAMES*FRAMESIZE)

plt.plot(decoded)
plt.title('Aufnahme von "Hallo"')
plt.xlabel('Time')
plt.ylabel('Amplitude [Digital Number]')
plt.savefig('AufnahmeHallo.png')
plt.show()

decodedWithTimestamp = numpy.zeros((decoded.size,2))

for i in range(decoded.size):
    decodedWithTimestamp[i,0] = decoded[i]
    decodedWithTimestamp[i,1] = abtastintervall * (i)

numpy.savetxt("hallo.csv", decodedWithTimestamp, delimiter=",")