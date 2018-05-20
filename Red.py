#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from visualization_msgs.msg import *

def callback(msg):
    message = "recieved  " + msg.data
    print(message)
    

def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    #sub = rospy.Subscriber("chatter",String,callback)

    pub_marker = rospy.Publisher('marker_py', Marker , queue_size=1)

    rospy.init_node('talker', anonymous=True)

    rate = rospy.Rate(10) # 10hz

    M = Marker();
    shape = M.CUBE;

    M.header.frame_id = "/my_py";
    M.header.stamp = rospy.get_rostime();
    
    M.ns = "py";
    
    M.id = 1;
    
    M.type = shape;
    
    M.action = Marker.ADD;

    
    M.pose.position.x = 1.0;
    
    #M.markers[i].pose.position.x = 2*(-j) + 1;

    M.pose.position.y = 0.0;
    #k++;
    M.pose.position.z = 0;

    x = M.pose.position.x
    y =  M.pose.position.y

    M.pose.orientation.x = 0.0;
    M.pose.orientation.y = 0.0;
    M.pose.orientation.z = 0.0;
    M.pose.orientation.w = 1.0;
    
    M.scale.x = 1.0;
    M.scale.y = 1.0;
    M.scale.z = 1.0;
    
    M.color.r = 0.0;
    M.color.g = 1.0;
    M.color.b = 0.0;
    M.color.a = 1.0;

    M.lifetime = rospy.Duration();



    while not rospy.is_shutdown():
        hello_str = "hello world %s" % rospy.get_time()
        #rospy.loginfo(hello_str)
        print(hello_str)
        pub.publish(hello_str)
        pub_marker.publish(M)

        M.pose.position.y = y + 0.1
        y =  M.pose.position.y

        rate.sleep()




if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
