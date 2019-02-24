import Adafruit_DHT
import urllib
import time

sensor = Adafruit_DHT.DHT22

pin = 23

while True: 
	humedad, temperatura = Adafruit_DHT.read_retry(sensor, pin)
	if humedad is not None and temperatura is not None:
		print('Temperatura={0:0.1f}*C  Humedad={1:0.1f}%'.format(temperatura,humedad))
	else:
		print('Fallo la lectura del sensor.Intentar de nuevo')

	time.sleep(5) 


