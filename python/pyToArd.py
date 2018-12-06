#This is a file that defines a function that wil write a string to the arduino.

import serial
import time
rf0 = '/dev/rfcomm0'
rf1 = '/dev/rfcomm1'
rf2 = '/dev/rfcomm2'
rf3 = '/dev/rfcomm3'
rf4 = '/dev/rfcomm4'
usb = '/dev/ttyUSB0'

def writeToArd(string):
# This function takes a string and sends it over the defined serial port
# this is acheived by converting to a ascii encoded byte array.
# args: string
# returns: nothing
    serialport = "/dev/rfcomm1"
    #initialize an serial port arduino instance
    ard = serial.Serial(serialport, 9600, timeout = 5)

    #wait for arduino to be ready
    time.sleep(0.2)

    # write length of string
    strLen = len(string) # find length of string so that arduino can init a buf
    strLen = bytearray([strLen]) # send str len first
    ard.write(strLen)
    time.sleep(0.1)

    # write string to arduino
    ard.write(bytearray(string, 'ascii'))
    print(string, "sent successfully")



if __name__ == "__main__":
    writeToArd(rf0, 9600, "test")
