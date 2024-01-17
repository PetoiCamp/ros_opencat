#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import JointState
from std_msgs.msg import Header, Float64
import math

def mover():
    pub = rospy.Publisher('joint_states', JointState, queue_size=10)
    rospy.loginfo('Joint_controller_Node Begins')
    rospy.init_node('joint_state_publisher_gui')
    rate = rospy.Rate(10) # 10hz 
    
    while not rospy.is_shutdown():
        js = JointState()
        js.header = Header()
        js.header.stamp = rospy.Time.now()
        js.name = ['neck_joint', 'shrfs_joint', 'shrft_joint', 'shrrs_joint', 'shrrt_joint', 'shlfs_joint', 'shlft_joint', 'shlrs_joint', 'shlrt_joint']
        js.position = [-0.57, -0.57, 1.14, 0.57, 1.14, -0.57, 1.14, 0.57, 1.14]  # Joint Angles copied from OpenCat Bittle Array and converted theta angles to radians. 
        js.velocity = []
        js.effort = []
        pub.publish(js)
        rate.sleep()

if __name__ == '__main__':
    try:
        mover()
    except rospy.ROSInterruptException:
        pass
