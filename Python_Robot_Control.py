import math
import numpy as np
import struct
import serial.tools.list_ports

from utils import *
from Python_Serial_Comm import * # for Serial Communication with Arduino
from Python_Kinematics import * # for robot FK and IK calculation
from Python_Keyboard import * # for keyboard control

# placeholder states
SerialConnection = True
SerialMessageMakesSense = True

openPortForSerial()
oldjoints = [90,90,80,90,80,90,80]

while (SerialConnection == True):
    if (SerialMessageMakesSense == True):
        # read Arduino Serial
        # parse?
        # compute or update current FK
        # read keyboard input
        # compute desired IK


        joints = randomJoints(oldjoints)
        jointsMsg = formatSerialMsg(joints)
        sendJointsBySerial(jointsMsg)
        oldjoints = joints

    else:
        print("error and exception handling")
        serialInst.close()
        exit()
        # error and exception handling
