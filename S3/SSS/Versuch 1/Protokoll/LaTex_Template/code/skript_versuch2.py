import numpy as np
import matplotlib.pyplot as p;

# AUFGABE 2

# Manuell erfassten Spannungswerte
arrayMean = [1.353, 1.139, 0.972, 0.866, 0.752, 0.713, 0.671, 0.635, 0.616, 0.608, 0.553,
             0.545, 0.610, 0.627, 0.610, 0.565, 0.523, 0.525, 0.514, 0.448]
arrayDistance = [100, 140, 180, 220, 270, 300, 330, 370, 400, 430, 470, 500, 520, 550,
                 570, 600, 620, 650, 670, 700]

# Alle Spannungen und Distanzen logarithmieren
logVoltage = np.log(arrayMean)
logDistance = np.log(arrayDistance)

# Berechnung der Mittelwerte
meanLogVoltage = logVoltage.mean()
meanLogDistance = logDistance.mean()

# Zusammenhang zwischen logarithmierte Distanz und logarithmiere Spannung
p.plot(logVoltage, logDistance)
p.ylabel('log Distance [mm]')
p.xlabel('log Voltage [V]')
p.show()

# Einzelne Paare ausgeben. Werden für die Erstellung der Tabelle benötigt
for i in range(len(logVoltage)):
    print("Log voltage: %.5f, Log dist: %.5f" % (logVoltage[i], logDistance[i]))

a1 = 0
a2 = 0

# Berechnung von a1 und a2 für lineare Regression
for i in range(len(logVoltage)):
    a1 += (logVoltage[i] - meanLogVoltage) * (logDistance[i] - meanLogDistance)
    a2 += pow((logVoltage[i] - meanLogVoltage), 2)
    
# Berechnung der a und b Parameter
a = a1 / a2
b = meanLogDistance - a * meanLogVoltage

# Ausgabe der Parameter
print("Variablen für Lineare Regression")
print("a: %f" % (a))
print("b: %f" % (b))
print("")

# Abbildung Ausgleichsgerade y'= a*x' + b
p.plot(logVoltage, logDistance, 'bo')
p.plot(logVoltage, [a * x + b for x in logVoltage])
p.title("ln y = a * ln x")
p.ylabel("log Distance [mm]")
p.xlabel("log Voltage [V]")
p.show()

# Abbildung y = exp(a * lnx + b)
p.plot(arrayMean, [np.exp(a * x + b) for x in logVoltage])
p.title("y = exp(a * ln x + b)")
p.ylabel("Distance [mm]")
p.xlabel("Voltage [V]")
p.show()
