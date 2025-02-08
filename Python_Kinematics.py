from utils import *
import math
import numpy as np
from scipy.spatial.transform import Rotation as R

PI = np.pi
# robot DH paramenter definition
# array is size 7, index 0 is place holder  
a = np.array([0,0,0,0,0,0,0]) # z-axis dist diff along x-axis
alpha = np.array([0,0,PI/2,-PI/2,PI/2,-PI/2,PI/2]) # z-axis angle diff about x-axis
d = np.array([0,L1,0,L2,0,L3,0]) # x-axis dist diff along z-axis
theta = np.array([0,0,0,0,0,0,0]) # x-axis angle diff about z-axis


class FKSolver:
    def FK(joints):
        q = np.array(joints)
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