import paho.mqtt.client as mqtt
from threading import Thread

print("Bienvenidos al chat")
nombre = input("Hola dime tu nombre: ")
nombre = nombre.capitalize()

def ante_conexion_exitosa(client,userdata,flags,rc):
    print("Conectados con exito")
    client.subscribe("l4GFVje7zy7jB1Y")
    client.publish("l4GFVje7zy7jB1Y",nombre+"se ha sumado al chat")

def ante_llegada_mensaje(client,userdata,msg):
    print(msg.payload.decode("utf-8"))
cliente = mqtt.Client()
cliente.on_connect = ante_conexion_exitosa
cliente.on_message = ante_llegada_mensaje
cliente.username_pw_set("48hsYf7kthMm3Sr","Tv7qInpl3cQA0SR")
cliente.connect("ioticos.org",1883,60)
while True:
    a_enviar=input("escribe un mensaje ->")
    a_envir = nombre + "dice"+ a_enviar
    cliente.publish("l4GFVje7zy7jB1Y",a_enviar)
    cliente.loop()


