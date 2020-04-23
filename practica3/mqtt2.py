import paho.mqtt.client as mqtt


def on_connect(client,userdata,flags,rc):
    print("Conectados con exito")
    client.subscribe("topic")

def on_message(client,userdata,msg):
    print(msg.payload.decode("utf-8"))
    
    
cliente = mqtt.Client()
cliente.on_connect = on_connect
cliente.on_message = on_message
#cliente.username_pw_set("usuario","contraseña")
cliente.connect("Servidor",1883,60)


while True:
    
    a_enviar=input("escribe un mensaje ->")
    cliente.publish("topic",a_enviar)
    cliente.loop()

