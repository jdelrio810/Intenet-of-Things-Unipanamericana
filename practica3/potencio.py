import urllib
import ssl
import sys
import serial
import time
#Cambiar API_KEY por la clave de la plataforma
#Dependiendo de si es omega o Raspberry PI el valor ttyS1 puede cambiar a ttyACM0, consulte con su profesor

url="https://api.thingspeak.com/update?api_key=API_KEY"

while True:
 puerto=serial.Serial('/dev/ttyS1', baudrate=9600, timeout=1.0 )
 linea=puerto.readline()
 puerto.close() 
 f=urllib.urlopen(url+"&field1=%s"%(linea))
 print f.read()
 print url+"&field1=%s"%(linea)
 #print(linea) 
 time.sleep(15)
