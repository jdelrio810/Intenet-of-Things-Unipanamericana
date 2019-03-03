import smtplib
import RPi.GPIO as GPIO
import time
from email.mime.text import MIMEText

GPIO.setmode(GPIO.BCM)

INPUT_PIN=4

GPIO.setup(INPUT_PIN,GPIO.IN)

while True:
	value=GPIO.input(INPUT_PIN)
	print(value)

	if value==True:
		print("El switch esta en  ON, enviando email de alerta....")
		msg=MIMEText("La luz del cuarto esta encendida  ")
	else:
		print("El switch esta en OFF, enviando email de alerta...")
		msg=MIMEText("la luz del cuarto esta apagada ")

	server=smtplib.SMTP('smtp.gmail.com',587)
	server.starttls()
	server.login('unipanamericanaiot@gmail.com','*********')
	msg['Subject']="Aviso de Iot Unipanamericana"
	server.sendmail("unipanamericanaiot@gmail.com","cualquiercorreo@xxxxx.com",msg.as_string())
	print("Email enviado")
	server.quit()
	time.sleep(60)
