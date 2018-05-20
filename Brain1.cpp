#include "ros/ros.h"
#include "gazebo_msgs/SetModelState.h"
#include "geometry_msgs/Twist.h"
#include <gazebo_msgs/ModelState.h>
#include "gazebo_msgs/ContactsState.h"
#include "std_msgs/String.h"
#include "std_msgs/Char.h"
#include <string>
#include "geometry_msgs/Vector3.h"
#include <cstddef>
#include "husky_msgs/brain1.h"
#include "nav_msgs/Odometry.h"

using namespace std;
#define pi 3.14

float X1,Y1,theta1;

void current_pos1(const nav_msgs::Odometry::ConstPtr& msg)
{
  //ROS_INFO("Seq: [%d]", msg->header.seq);
  /*ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
  */
  /*POS_X = static_cast<int>(std::round(msg->pose.pose.position.x));
  POS_Y = static_cast<int>(std::round(msg->pose.pose.position.y));
  POS_Z = static_cast<int>(std::round(msg->pose.pose.position.z));
  ANGLE_MADE = static_cast<int>(std::round(10*msg->pose.pose.orientation.z));
  */
  X1 =      msg->pose.pose.position.x;
  Y1 =      msg->pose.pose.position.y;
  //z1 = 	   msg->pose.pose.position.z ;
  theta1 = msg->pose.pose.orientation.z;
  std::cout<<"POS OF ROBO 1 : "<<"X1: "<<X1<<" "<<"Y1 : "<<Y1<<" "<<" theta1: "<<theta1*pi<<endl;
}  



int main(int argc, char **argv){

	ros::init(argc,argv,"Brain1");
	ros::NodeHandle n;
	
	//MESSAGE TO Move telling where to go : aection 
	ros::Publisher chatter1_pub = n.advertise<std_msgs::Char>("brain1_to_move", 1000);	
	ros::Publisher vel1_pub = n.advertise<geometry_msgs::Twist>("/husky1/husky_velocity_controller/cmd_vel", 10);
	ros::Subscriber sub_pos1 = n.subscribe("/husky1/ground_truth/state", 100,current_pos1);
	
	ros::Rate loop_rate(10);
	ros::Time ros_time;
	//husky_msgs::brain1 message;
	//std_msgs::Char message;
	geometry_msgs::Twist vel1;
	float X2 ,Y2 , tol;
	std::cout<<"enter where to move = floats X and Y and Tolerance"<<endl;
	std::cin>>X2>>Y2>>tol;
	while(ros::ok()){
/*		char a = ' ';
		std::cout<<"Enter where to move \n";
		std::cin>>a;
		std::cout<<a<<" here \n";
		
		message.data = a;
		geometry_msgs::Twist vel1;
		chatter1_pub.publish(message);

		if(a == 'w'){ //FORWARD
			vel1.linear.x  =  0.1;
			vel1.angular.z =  0.1;
			std::cout<<"Moving Forward"<<"\n";
			// we need to make flag zero for any change in the coordinates of x1,y1
			 
			ros::Duration(0.1);
		}else if(a == 'a'){ // LEFT TURN
			vel1.linear.x  =   0.0;
			vel1.angular.z =  -0.5;
			
			ros::Duration(0.1);			
		}else if(a == 'd'){           // RIGHT
			vel1.linear.x  =  0.0;
			vel1.angular.z =  0.5;
			
			ros::Duration(0.1);			
		}else if(a == 's'){				//BACK
			vel1.linear.x  =  -0.5;
			vel1.angular.z =   0.0;
			
			ros::Duration(0.1);			
		}else{  			// STOP
			vel1.linear.x  =   0.0;
			vel1.angular.z =   0.0;
			std::cout<<"STOP"<<"\n";
			ros::Duration(0.1);						
		}
*/		if(std::sqrt(std::pow(Y1 - Y2,2) + std::pow(X1 - X2,2)) > tol){
			if(abs(Y2-Y1) > abs(X2 -X1))
				vel1.linear.x = 1*(Y2 - Y1);
			else
				vel1.linear.x = 1*(X2 - X1);	
			if(abs(theta1*pi -  std::atan2(Y2 - Y1 , X2 - X1)) > 0.05)
				vel1.angular.z = 0.4*std::atan2(Y2 - Y1 , X2 - X1); //this gives angle in radians
			else
				vel1.angular.z = 0.0;	
			/*	if(vel1.angular.z > 0.3)
					vel1.angular.z = 0.3;
				else if(vel1.angular.z < -0.3)
					vel1.angular.z = -0.3;*/		
		}else{
			vel1.linear.x  = 0.0;
			vel1.angular.z = 0.0;
		}
		std::cout<<"Speed = "<<vel1.linear.x<<"  Angular rotation = "<<vel1.angular.z<<endl;
		std::cout<<"Difference between X "<<X2-X1<<"  Y = "<<Y2-Y1<<endl;
		vel1_pub.publish(vel1);
		//vel2_pub.publish(vel2);
		
		ros::spinOnce();
		loop_rate.sleep();
	}	
	return 0;	
}	
