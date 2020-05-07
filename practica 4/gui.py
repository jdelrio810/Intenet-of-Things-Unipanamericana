import tkinter as tk
import numpy as np
import random
import time
import datetime
import threading


#pin = 4
#sensor = Adafruit_DHT.DHT22

def tick():

    time2=time.strftime('%H:%M:%S')
    clock.config(text=time2)
    clock.after(200,tick)


def get_data():

    threading.Timer(2, get_data).start()
    temperatura = "29"
    l_display.config(text = temperatura)
    return temperatura



mainwindow = tk.Tk()
mainwindow.geometry('640x340')
mainwindow.title("Sensor de Temperatura ")

clock=tk.Label(mainwindow,font=("Arial",20),fg="black")
clock.grid(row=0, column=0, padx=5, pady=5, sticky="nsew")

l_m=tk.Label(mainwindow,text="Sensor de Temperatura",bg='blue',font=("Arial",20),fg="white")
l_m.grid(row=0,column=1, padx=10, pady=10, sticky="nsew")

l_t=tk.Label(mainwindow, text="Temperatura :",font=("Arial",25))
l_t.grid(row=3,column=0, padx=10, pady=10, sticky="nsew")

l_display=tk.Label(mainwindow,font=("Arial",25),fg="red")
l_display.grid(row=3,column=1, padx=10, pady=10, sticky="nsew")


tick()
get_data()

mainwindow.mainloop()

