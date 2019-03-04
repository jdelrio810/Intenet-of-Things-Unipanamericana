import RPi.GPIO as GPIO                    
import time                                
GPIO.setmode(GPIO.BCM)                     

TRIG = 23                                  
ECHO = 24                                  
V    = 34300			    			   

print "Medicion de la distancia en curso"

GPIO.setup(TRIG,GPIO.OUT)                  
GPIO.setup(ECHO,GPIO.IN)                   

GPIO.output(TRIG, False)                   
print "Espere que el sensor se estabilice"
time.sleep(2)                              

GPIO.output(TRIG, True)                    
time.sleep(0.00001)                        
GPIO.output(TRIG, False)                   

while GPIO.input(ECHO)==0:                 
  pulse_start = time.time()                

while GPIO.input(ECHO)==1:                 
  pulse_end = time.time()                  

t = pulse_end - pulse_start                

distancia = t * (V/2)                      
distancia = round(distancia, 2)            

if distancia > 2 and distancia < 400:      

  print "Distancia: ",distancia,"cm"        

else:
  print "Fuera de Rango"                   

GPIO.cleanup()							   	
