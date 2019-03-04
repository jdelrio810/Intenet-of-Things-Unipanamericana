import Adafruit_DHT
import urllib.request
import time
import requests

url_thingtweet= "https://api.thingspeak.com/apps/thingtweet/1/statuses/update"
data = {"api_key":"xxxxxxxxxxx","status":"Dejastes la luz prendida..."}

GPIO.setmode(GPIO.BCM)
INPUT_PIN=4
GPIO.setup(INPUT_PIN,GPIO.IN)

while True:
	value=GPIO.input(INPUT_PIN)
	print(value)

	if value==True:
		print("El switch esta en  ON, enviando twitter de alerta....")
		resp =requests.post(url_thingtweet,json=data)
		print("twitter enviado")
	else:
		print("El switch esta en OFF...No hay problema..")
		
	time.sleep(60)
