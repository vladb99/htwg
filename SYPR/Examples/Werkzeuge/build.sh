#!/bin/sh
for s in hallo.c gruss.c ; do
  compile_command="gcc -c $s"  # Variable mit Initialisierung
  echo $compile_command        # Wert der Variablen ausgeben
  eval $compile_command        # Wert der Variablen als Kommando ausfuehren
  if [ $? -ne 0 ] ; then       # Rueckgabewert des Kommandos prüfen
    echo build failed
    exit 1
  fi
done

link_command="gcc -o hallo hallo.o gruss.o"
echo $link_command
eval $link_command
if [ $? -ne 0 ] ; then
  echo build failed
  exit 1
fi

echo build successful

