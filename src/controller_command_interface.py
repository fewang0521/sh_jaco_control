#!/usr/bin/env python

import rospy
from sh_jaco_arm_control.msg import JacoGripperCommand
from std_msgs.msg import Float64
from random import random

def callback(msg):
    pub_0.publish(msg.finger_0)
    pub_2.publish(msg.finger_2)
    pub_4.publish(msg.finger_4)

rospy.init_node('contoller_msg_interface')
pub_0 = rospy.Publisher('/jaco/finger_controller_0/command', Float64)
pub_2 = rospy.Publisher('/jaco/finger_controller_2/command', Float64) 
pub_4 = rospy.Publisher('/jaco/finger_controller_4/command', Float64)

sub = rospy.Subscriber('/jaco/gripper_interface', JacoGripperCommand, callback)

rospy.spin()
