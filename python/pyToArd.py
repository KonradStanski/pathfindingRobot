#This is a file that defines a function that wil write a string to the arduino.

import serial
import time
rf0 = '/dev/rfcomm0'
rf1 = '/dev/rfcomm1'
rf2 = '/dev/rfcomm2'
rf3 = '/dev/rfcomm3'
rf4 = '/dev/rfcomm4'
usb = '/dev/ttyUSB0'

def writeToArd(port, baudrate, string):

    #initialize an serial port arduino instance
    ard = serial.Serial(port, baudrate, timeout = 5)

    #wait for arduino to be ready
    time.sleep(0.2)

    # write length of string
    strLen = str(len(string)) # find length of string so that arduino can init a buf
    strLen = bytearray(strLen, 'ascii') # send str len first
    ard.write(strLen)
    time.sleep(0.1)

    # write string to arduino
    ard.write(bytearray(string, 'ascii'))
    print(string, "sent")



if __name__ == "__main__":
    writeToArd(rf4, 9600, "test")

#val1 = bytearray("SSSNNNWNWEEEWNWEWNWNWNSNWEWSN", 'ascii') # defining ascii encoding
#ard.write(val1)

#val2 = bytearray(b'W') # just calling it binary
#ard.write(val2)


