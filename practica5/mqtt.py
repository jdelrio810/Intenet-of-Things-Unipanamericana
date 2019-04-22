#!/usr/bin/env python 1
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import sys

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Conectado - Codigo de resultado: "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

try:
    client.connect("m10.cloudmqtt.com",12278, 60)
except:
    print("No se pudo conectar con el MQTT Broker...")
    print("Cerrando...")
    sys.exit()
    
client.username_pw_set("¨¨¨¨¨¨", "*********")

try:
    client.loop_forever()
except KeyboardInterrupt:  #precionar Crtl + C para salir
    print("Cerrando...")
