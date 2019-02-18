
import Adafruit_DHT
import urllib
import time

sensor = Adafruit_DHT.DHT22


pin = "P8_11"
humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)

if humidity is not None and temperature is not None:
    print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
else:
    print('Failed to get reading. Try again!')

baseUrl="https://api.thingspeak.com/update?api_key=APIKEY"
while True:
  
  f=urllib.urlopen(baseUrl+"&field1=%s&field2=%s"%(temperature,humidity))
  print f.read()
  print baseUrl+"&field1=%s&field2=%s"%(temperature,humidity) 
  f.close()

time.sleep(25) 
