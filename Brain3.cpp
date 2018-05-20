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
#include "husky_msgs/brain2.h"
#include "nav_msgs/Odometry.h"

float X1=0.0,Y1=0.0,Z1=0.0,theta1=0.0;
float X2=0.0,Y2=0.0,Z2=0.0,theta2=0.0;

int count=0;
int follow = 1;
int flag ;

#define pi 3.14
using namespace std;

void current_pos1(const nav_msgs::Odometry::ConstPtr& msg)
{
  //ROS_INFO("Seq: [%d]", msg->header.seq);
  /*ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
  */
  /*X = static_cast<int>(std::round(msg->pose.pose.position.x));
  Y = static_cast<int>(std::round(msg->pose.pose.position.y));
  Z = static_cast<int>(std::round(msg->pose.pose.position.z));
  ANGLE_MADE = static_cast<int>(std::round(10*msg->pose.pose.orientation.z));
  */
  X1 =      floor(msg->pose.pose.position.x * 10)/10;
  Y1 =      floor(msg->pose.pose.position.y * 10)/10;
  Z1 = 	   floor(msg->pose.pose.position.z * 10)/10;
  theta1 = floor(10*msg->pose.pose.orientation.z * 10)/10;
  //ROS_INFO("%f ,%f ,%f ,%f ,%f ,%f \n",X,Y,Z,ANGLE_MADE,IniX,IniAngleMade);
}

void current_pos2(const nav_msgs::Odometry::ConstPtr& msg)
{
  //ROS_INFO("Seq: [%d]", msg->header.seq);
  /*ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
  */
  /*X = static_cast<int>(std::round(msg->pose.pose.position.x));
  Y = static_cast<int>(std::round(msg->pose.pose.position.y));
  Z = static_cast<int>(std::round(msg->pose.pose.position.z));
  ANGLE_MADE = static_cast<int>(std::round(10*msg->pose.pose.orientation.z));
  */
  X2 =      floor(msg->pose.pose.position.x * 10)/10;
  Y2 =      floor(msg->pose.pose.position.y * 10)/10;
  Z2 = 	   floor(msg->pose.pose.position.z * 10)/10;
  theta2 = floor(10*msg->pose.pose.orientation.z * 10)/10;
  //ROS_INFO("%f ,%f ,%f ,%f ,%f ,%f \n",X,Y,Z,ANGLE_MADE,IniX,IniAngleMade);

}

geometry_msgs::Twist move(int &flag)
{
	geometry_msgs::Twist vel2;
	std::cout<<"Enetered MOVE"<<endl;
	std::cout<<"Y1 "<<Y1<<" X1: "<<X1<<" theta1: "<<theta1<<" "<<"atan2: "<<std::atan2(Y1,X1)*180/pi<<"   robo2  "<<"Y2: "<<Y2<<" X2: "<<X2<<" theta2: "<<theta2<<"  atan2: "<<std::atan2(Y2,X2)*180/pi<<endl;
	std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	//while(fabs(theta2*90 - (1/2)*(225.0 - std::atan2(Y2,X2) - std::atan2(Y1,X1))) > 0.1)
	while(fabs(90*theta2 - std::atan2(Y1,X1)*180/pi) > 8) //these are degrees
	{
		//assign angular to 2
		std::cout<<"in while loop 1"<<endl;
		vel2.angular.z = 0.2;		
		flag = 0;
		follow = 1;
		ros::Duration(0.05);
		//vel2_pub.publish(vel2);
		return vel2;
		
	}

	while(fabs((Y2 + X2) - (Y1 + X1)) < 0.1){ //equation of line : y = -x + y1 + x1. So new x2,y2 will lie on this
		//assign linear x to 2
		std::cout<<"in while loop 2"<<endl;
		vel2.linear.x = 0.5;	
		flag = 0;	
		follow = 1;
		ros::Duration(0.1);
		//vel2_pub.publish(vel2);
		return vel2;
	}

	flag = 1;	
}

int main(int argc, char **argv){

	ros::init(argc,argv,"Brain2");
	ros::NodeHandle n;
	
	//MESSAGE TO Move telling where to go : direction 
	ros::Publisher chatter2_pub = n.advertise<std_msgs::Char>("brain2_to_move", 1000);	
	ros::Publisher vel2_pub = n.advertise<geometry_msgs::Twist>("/husky3/husky_velocity_controller/cmd_vel", 10);

	ros::Subscriber sub_pos1 = n.subscribe("/husky1/ground_truth/state", 1000, current_pos1);
	ros::Subscriber sub_pos2 = n.subscribe("/husky2/ground_truth/state", 1000, current_pos2);

	ros::Rate loop_rate(10);
	ros::Time ros_time;
	//husky_msgs::brain2 message;
	geometry_msgs::Twist vel2;
	std_msgs::Char message;
	char a = ' ';
	while(ros::ok()){
	
	//std::cout<<"enter value of follow"<<endl;
	
	/*if(flag == 1) //if flag == 0 then keep following
		std::cin>>follow;

	if(follow == 0){
		std::cout<<"Enter where to move";
		std::cin>>a;
		std::cout<<a<<" here \n";
		
		message.data = a;
		
		chatter2_pub.publish(message);

		if(a == 'w'){ //FORWARD
			vel2.linear.x  =  0.5;
			vel2.angular.z =  0.0;
			std::cout<<"Moving Forward"<<"\n";
			// we need to make flag zero for any change in the coordinates of x1,y1
			 
			ros::Duration(0.1);
		}else if(a == 'a'){ // LEFT TURN
			vel2.linear.x  =   0.0;
			vel2.angular.z =  -0.5;
			
			ros::Duration(0.1);			
		}else if(a == 'd'){           // RIGHT
			vel2.linear.x  =  0.0;
			vel2.angular.z =  0.5;
			
			ros::Duration(0.1);			
		}else if(a == 's'){				//BACK
			vel2.linear.x  =  -0.5;
			vel2.angular.z =   0.0;
			
			ros::Duration(0.1);			
		}else{  			// STOP
			vel2.linear.x  =   0.0;
			vel2.angular.z =   0.0;
			std::cout<<"STOP"<<"\n";
			ros::Duration(0.1);						
		}
	}else{
		flag = 0;*/

		//vel2 = move(flag);
		case(state)
		vel2.linear.x = -0.1;

		vel2_pub.publish(vel2);
		ros::Duration(0.1);
		//vel2_pub.publish(vel2);
		
		ros::spinOnce();
		loop_rate.sleep();
	}	

	return 0;
}

