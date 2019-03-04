import Adafruit_DHT
import urllib.request
import RPi.GPIO as GPIO
import time
import requests

GPIO.setmode(GPIO.BCM)
INPUT_PIN=4
GPIO.setup(INPUT_PIN,GPIO.IN)

while True:
	value=GPIO.input(INPUT_PIN)
	print(value)

	if value==True:
		print("El switch esta en  ON, enviando twitter de alerta....")
		resp =requests.post("xxxxxxxxxxxxxxxx")
		print("twitter enviado")
	else:
		print("El switch esta en OFF...No hay problema..")
		
	time.sleep(60)
