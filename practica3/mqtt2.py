import paho.mqtt.client as mqtt


nombre = input("Hola dime tu nombre: ")
nombre = nombre.capitalize()

def on_connect(client,userdata,flags,rc):
    print("Conectados con exito")
    client.subscribe("topic")
    client.publish("topic",nombre)

def on_message(client,userdata,msg):
    print(msg.payload.decode("utf-8"))
    
cliente = mqtt.Client()
cliente.on_connect = on_connect
cliente.on_message = on_message
cliente.username_pw_set("usuario","contraseña")
cliente.connect("ioticos.org",1883,60)


while True:
    a_enviar=input("escribe un mensaje ->")
    a_envir = nombre + "dice"+ a_enviar
    cliente.publish("topic",a_enviar)
    cliente.loop()


