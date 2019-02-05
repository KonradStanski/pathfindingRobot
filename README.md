# Pathfinding Arduino Rover

## Included Files:
    Readme
    outline.txt
        Python/
            maze.py
            pathfinding.py
            pyToArd.py
            mazes/
                maze1_11X11.gif
                maze_big.gif
            soln_mazes/
                maze1_11X11_soln.gif
                maze_big_soln.gif
        Arduino/
            Makefile
            main.cpp


## Running Instructions:
    1. Wire the Arduino as detailed in the wiring instructions below
    2. Configure the makefile as detailed below
    3. Make and upload to the arduino
    4. Connect with your computer to the bluetooth module using bluetooth manager
    5. Determine what /dev/*** port it is connected to in bluetooth manager
    6. Modify the port in writeToArd() function in pyToArd.py
    7. Generate maze using reference website and crop white border or use example maze
    8. Specify maze name and path in maze.py
    9. Turn on arduino connected to appropriate power source
    10. For debug output, in a terminal open sudo minicom to the same /dev/**** as sepcified in pathfinding.py
    11. Run sudo python3 pathfinding.py
    12. The robot will now run the maze and print its current state to the minicom terminal over bluetooth


## Python Requirments:
    pillow import as PIL
        sudo pip3 install pillow
    time import as time
    numpy import as numpy
        sudo pip3 install numpy
    pyserial import as serial
        sudo pip3 install pyserial


## Wiring instructions:
    //Stepper Drivers
    Arduino digital pin 3     // IN1 on the ULN2003 driver 1
    Arduino digital pin 4     // IN2 on the ULN2003 driver 1
    Arduino digital pin 5     // IN3 on the ULN2003 driver 1
    Arduino digital pin 6     // IN4 on the ULN2003 driver 1
    Arduino digital pin 8     // IN1 on the ULN2003 driver 2
    Arduino digital pin 9     // IN2 on the ULN2003 driver 2
    Arduino digital pin 10    // IN3 on the ULN2003 driver 2
    Arduino digital pin 11    // IN4 on the ULN2003 driver 2
    5-12V Power Source        // +VCC on ULN2003 driver 1 and 2
    Arduino GND               // GND on ULN2003 driver 1 and 2

    //Bluetooth
    Arduino digital pin 14 TX // RX on HC-05 Module
    Arduino digital pin 15 RX // TX on HC-05 Module
    Arduino 5-12V             // VCC on HC-05 Module
    Arduino GND               // GND on HC-05 Module

    //Arduino
    5-12V Power Source        // Arduino VIN
    GND Power Source          // Arduino GND

## Makefile Configuration and Requirments for Arduino:
    In order to make main.cpp, you need to navigate to /usr/share/arduino/libraries
    and copy the Servo Library and copy it to /arduino-ua/libraries
    It is also necessary to download the virtualWire library from:
    https://platformio.org/lib/show/251/VirtualWire
    and place it in /arduino-ua/libraries.

    You then need to go into the provided arduino makefile and modify the entry that
    defines what user libraries to include in the make.
    To do this you simply add the name of the folders. it should now look like this:
    ARDUINO_LIBS = SD SPI Adafruit_GFX Adafruit_ILI9341 TouchScreen AccelStepper


## Resources:
    maze generation:
    https://hereandabove.com/maze/mazeorig.form.html

    Stepper Control:
    http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html
    https://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/

    Comms:
    http://www.userk.co.uk/arduino-bluetooth-linux/
    https://botforge.wordpress.com/2016/07/26/the-right-way-to-connect-an-hc-05-bluetooth-module-to-an-arduino/


## Notes:
    Serial port is defined in writeToArd() function in pyToArd.py
    Function comments can be found with the functions
