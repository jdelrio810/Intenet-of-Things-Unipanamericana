import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT) 

def blink():
        print("Ejecucion iniciada...")
        iteracion = 0
        while iteracion < 30: ## Segundos que durara la funcion
                GPIO.output(18, True) 
                time.sleep(1) 
                GPIO.output(18, False)
                time.sleep(1) 
                iteracion = iteracion + 2
        print ("Ejecucion finalizada")
        GPIO.cleanup() 
blink()
