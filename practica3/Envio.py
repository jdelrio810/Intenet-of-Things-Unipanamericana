import serial
import time

#arduino=serial.Serial('/dev/ttyUSB0',baudrate=115200, timeout = 1.0)


while True:
	arduino=serial.Serial('/dev/ttyUSB0',baudrate=115200, timeout = 1.0)
	inputPin = input("escribe una letra")
	inputPinStr = str(inputPin)
	inputPinStrBytes = inputPinStr.encode()
	arduino.write(inputPinStrBytes)
	time.sleep(0.1)
	arduino.close()
 
