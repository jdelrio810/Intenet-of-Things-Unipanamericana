import serial
import sys 

# make sure to use the correct serial serial communication device name 
# e.g. /dev/ttyUSB0, /dev/ttyUSB1, /dev/ttyACM0, ...
#  as you discovered in the steps above
# dmesg | grep -v disconnect | grep -Eo "tty(ACM|USB)." | tail -1
ser = serial.Serial('/dev/ttyUSB0', 115200)

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
