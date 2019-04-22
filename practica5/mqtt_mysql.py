#!/usr/bin/env python 1
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import sys
import MySQLdb

# Abrir conexiÃ³n con bases de datos
try:
    db = MySQLdb.connect("127.0.0.1","root","raspberry","mqtt")
except:
    print("No se pudo conectar con la base de datos")
    print("Cerrando...")
    sys.exit()

# Preparando cursor
cursor = db.cursor()

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Conectado - Codigo de resultado: "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    lista = msg.topic.split("/")

    sql = """INSERT INTO `mqtt`.`tabla` (`id`, `usuario`, `topic`, `mensaje`, `fecha`) VALUES (NULL, '""" + lista[1]+ """', '""" + lista[2] + """', '""" + str(msg.payload) + """', CURRENT_TIMESTAMP);"""

    try:
        # Ejecutar un comando SQL
        cursor.execute(sql)
        db.commit()
        print("Guardando en base de datos...OK")
    except:
        db.rollback()
        print("Guardando en base de datos...FallÃ³")
        
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

try:
    client.connect("m11.cloudmqtt.com", 14301, 60)
except:
    print("No se pudo conectar con el MQTT Broker...")
    print("Cerrando...")
    db.close()
    sys.exit()   
    
client.username_pw_set("xtvdpffw", "v19VYYxNfgE-")

try:
    client.loop_forever()
except KeyboardInterrupt:  #precionar Crtl + C para salir
    print("Cerrando...")
    db.close()
