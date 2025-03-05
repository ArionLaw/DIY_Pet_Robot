from utils import *
import math
import numpy as np
import time
import random
from scipy.spatial.transform import Rotation as R

PI = np.pi
# robot DH paramenter definition
# array is size 7, index 0 is place holder  
a = np.array([0,0,0,0,0,0,0]) # z-axis dist diff along x-axis
alpha = np.array([0,0,PI/2,-PI/2,PI/2,-PI/2,PI/2]) # z-axis angle diff about x-axis
L1 = 58
L2 = 80
L3 = 80
d = np.array([0,L1,0,L2,0,L3,0]) # x-axis dist diff along z-axis
theta = np.array([0,0,0,0,0,0,0]) # x-axis angle diff about z-axis
servoOffset = np.array([0,-PI/2,0,-PI/2,0,-PI/2,0]) # offset in 

jointMinLimit = np.array([0,0,0,0,0,0,0])
jointMaxLimit = np.array([180,180,180,180,180,180,180])
jointMinSoftLimit = np.array([20,20,40,20,20,20,20])
jointMaxSoftLimit = np.array([160,160,80,160,160,160,160])

class FKSolver:
    def FK(joints):
        q = np.array(joints)

        for i in range(1,len(joints),1):
            #get Ri
            #get xyzi
            xyz_EE = [x,y,z]
            R1 = RotMtx('x',0)@RotMtx('z',q[1])
            R2 = RotMtx('x',np.pi/2)@RotMtx('z',q[2])
            R3 = RotMtx('x',np.pi/2)@RotMtx('z',q[3])
            R4 = RotMtx('x',np.pi/2)@RotMtx('z',q[4])
            R5 = RotMtx('x',np.pi/2)@RotMtx('z',q[5])
            R6 = RotMtx('x',np.pi/2)@RotMtx('z',q[6])
            R_EE = R1@R2@R3@R4@R5@R6
            return xyz_EE,R_EE


class IKSolver:
    def IK(xyz_EE,R_EE):


        return joints
    

def randomJoints(q):
    delta = 20
    for i in range(7):
        a = q[i]-delta
        b = q[i]+delta
        if (q[i]-delta < jointMinSoftLimit[i]):
            a = jointMinSoftLimit[i]
        if (q[i]+delta > jointMaxSoftLimit[i]):
            b = jointMaxSoftLimit[i]
        q[i] = random.randrange(a,b,1)
        time.sleep(random.randrange(20,200,1)/1000)
    return q

def getTj(k, s, m, h):
    '''
    Helper function to get transformation matrix for bending portion.
    Result depends on if k is 0 (straight) or not.
    '''
    if k == 0:
        res = np.array([[1, 0, 0, 0],
                        [0, 1, 0, 0],
                        [0, 0, 1, h / m],
                        [0, 0, 0, 1]
                        ])
    else:
        theta = k*s / m
        res = np.array([[1, 0, 0, 0],
                        [0, np.cos(theta), -np.sin(theta),
                            (np.cos(theta)-1)/k],
                        [0, np.sin(theta), np.cos(theta), np.sin(theta)/k],
                        [0, 0, 0, 1]
                        ])
    return res