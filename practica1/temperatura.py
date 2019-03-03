import Adafruit_DHT
import urllib.request
import time

sensor = Adafruit_DHT.DHT22
pin = 23


while True: 
	humedad, temperatura = Adafruit_DHT.read_retry(sensor, pin)
	
	if humedad is not None and temperatura is not None:
		print('Temperatura={0:0.1f}*C  Humedad={1:0.1f}%'.format(temperatura,humedad))
	else:
		print('Fallo la lectura del sensor.Intentar de nuevo')

	url = "https://api.thingspeak.com/update?api_key=APIKEY"

	f=urllib.request.urlopen(url+"&field1="+str(temperatura)+"&field2="+str(humedad))
	#f=urllib.request.urlopen(baseUrl+"&field1=%s&field2=%s"%(temperatura,humedad))
	time.sleep(5) 
