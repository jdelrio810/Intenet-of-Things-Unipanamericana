import serial
import time


ser = serial.Serial('/dev/ttyS1', 115200)


# loop until manually stopped
# first flush possibly existing data in the input buffer:
ser.flushInput()
while True:
    try:
        # read a single line from the serial interface represented by the ser object
        
        lineBytes = ser.readline()
        # convert Bytes returned by the ser.readline() function to String
        line = lineBytes.decode('utf-8')
        # print the read line to the output
        print(line)
        
    except KeyboardInterrupt:
    	 break # stop the while loop
