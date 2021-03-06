#ifndef HUSKY_TEST_H
#define HUSKY_TEST_H


#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <string>
#include "geometry_msgs/Vector3.h"
#include "ros/ros.h"
#include "gazebo_msgs/SetModelState.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
//#include <math>
#include "std_msgs/Char.h"
#include "gazebo_msgs/ModelState.h"
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

class MoveHusky
{
	ros::NodeHandle n3,n1,n2;

	

	ros::Subscriber sub_pos1 , sub_pos2 , sub_pos3 , sub_pos4 , sub_pos5 , sub_pos6 , sub_pos7 , sub_pos8 , sub_pos9 ;
	ros::Subscriber sub_brain1;
	ros::Publisher  vel1_pub , vel2_pub , vel3_pub , vel4_pub , vel5_pub , vel6_pub , vel7_pub , vel8_pub , vel9_pub , marker_pub;

	geometry_msgs::Twist  vel1,vel2,vel3,vel4,vel5,vel6,vel7,vel8,vel9;	

	visualization_msgs::MarkerArray M;

	//float x1 ,Y1 ,z1,theta1 , x2,y2,z2,theta2 , x3,y3,z3,theta3 , x4,y4,z4,theta4 , x5,y5,z5,theta5 ;
	float x[10] , y[10] , theta[10] , z[10];
	float ini_theta2,ini_y2,ini_x2 , ini_theta3,ini_y3,ini_x3;
	char dir;
	int flag , flag2;	
	float markerX[10] , markerY[10];

	public:
		MoveHusky();
		~MoveHusky();

		//geometry_msgs::Twist move1();
		//geometry_msgs::Twist move2();
		void move2();
		void move1();
		void move3();
		void move4();
		void move5();
		void move6();
		void move7();
		void move8();
		void move9();

		void direction_to_move(const std_msgs::Char::ConstPtr& msg);
		
		void current_pos2(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos1(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos3(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos4(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos5(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos6(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos7(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos8(const nav_msgs::Odometry::ConstPtr& msg);
		void current_pos9(const nav_msgs::Odometry::ConstPtr& msg);

		
		void publish_marker();
		

};

#endif