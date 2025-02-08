import serial
import time

from serial.tools.list_ports import comports



for portItem in comports():
    print(portItem)

    arduinoSerial = serial.Serial(port='COM4',baudrate=9600,timeout=.5)

# check if port is open
arduinoSerial.is_open

# close port
arduinoSerial.close()

# type Arduino code and uplode Arduino code

# open port
arduinoSerial.open()

# joint values to send
joints=[0,90,90,90,90,90,90]
# convert array to string
serialMessage = str(joints)
# write serial message
arduinoSerial.write(bytes(serialMessage, 'utf-8'))

# wait for Arduino to process message
time.sleep(0.01)
# read the message that is available on the Serial port
readLine = arduinoSerial.readline()

#convert the Byte message to string
stringLine = readLine.decode("utf-8")