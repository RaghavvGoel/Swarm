#include "ros/ros.h"
#include "gazebo_msgs/SetModelState.h"
#include "geometry_msgs/Twist.h"
#include <gazebo_msgs/ModelState.h>
#include "gazebo_msgs/ContactsState.h"
#include "std_msgs/String.h"
#include <string>
#include "geometry_msgs/Vector3.h"
#include <cstddef>

using namespace std;

int main(int argc, char **argv){

	ros::init(argc,argv,"Red1");
	ros::NodeHandle n;
	
	ros::Publisher vel1_pub = n.advertise<geometry_msgs::Twist>("/husky1/husky_velocity_controller/cmd_vel", 10);
	ros::Publisher vel2_pub = n.advertise<geometry_msgs::Twist>("/husky2/husky_velocity_controller/cmd_vel", 10);
	
	
	ros::Rate loop_rate(10);
	ros::Time ros_time;
	geometry_msgs::Twist vel1,vel2;
	
	while(ros::ok()){
		vel1.linear.x = 0.4;
		vel1.angular.z = 0.0;	
		
		vel2.linear.x = -0.4;
		vel2.angular.z = 0.0;
		ros::Duration(0.1); 
		ROS_INFO("oyoy");

		vel1_pub.publish(vel1);
		vel2_pub.publish(vel2);
		ros::spinOnce();
		loop_rate.sleep();
	}	
	return 0;	
}	
