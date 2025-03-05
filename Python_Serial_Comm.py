# for serial communication using Pyserial
import serial
# time library for delays
import time
import numpy as np

import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()
portsList = []

def formatSerialMsg(message):
    serialMsg = repr(message)
    serialMsg = serialMsg.replace('array','').replace(' ','').replace("'",'').strip('()')
    return serialMsg


def sendJointsBySerial(jointsMsg):
    # joint values np.array format = [q0,q1,q2,q3,q4,q5,q6], size 7, first value is placeholder
    # convert array to string
    serialMessage = formatSerialMsg(jointsMsg)
    print(serialMessage)

    # write serial message
    serialInst.write(serialMessage.encode('utf-8'))

    # wait for Arduino to process message
    time.sleep(0.05)

def openPortForSerial():
    # printing port information
    for portItem in ports:
        portsList.append(str(portItem))
        print(portItem)

    comPortNum = input("Select COM Port for Arduino (format as int only): ")

    for i in range(len(portsList)):
        if portsList[i].startswith("COM" + str(comPortNum)):
            comPort = "COM" + str(comPortNum)

    serialInst.baudrate = 9600
    serialInst.port = comPort
    serialInst.open()