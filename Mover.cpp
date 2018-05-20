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
//#include <math.h>
#include "std_msgs/Char.h"
#include "gazebo_msgs/ModelState.h"
#include "husky_test.h"


using namespace std;

MoveHusky::MoveHusky()
{
	vel1_pub = n1.advertise<geometry_msgs::Twist>("/husky1/husky_velocity_controller/cmd_vel", 10);
	vel2_pub = n2.advertise<geometry_msgs::Twist>("/husky2/husky_velocity_controller/cmd_vel", 10);
	vel3_pub = n2.advertise<geometry_msgs::Twist>("/husky3/husky_velocity_controller/cmd_vel", 10);
	vel4_pub = n3.advertise<geometry_msgs::Twist>("/husky4/husky_velocity_controller/cmd_vel", 10);
	vel5_pub = n3.advertise<geometry_msgs::Twist>("/husky5/husky_velocity_controller/cmd_vel", 10);	

	//2 subscribers for current position : ODOMbrain1_to_move
	sub_pos1 = n1.subscribe("/husky1/ground_truth/state", 100, &MoveHusky::current_pos1, this);
	sub_pos2 = n2.subscribe("/husky2/ground_truth/state", 100, &MoveHusky::current_pos2,this);
	sub_pos3 = n2.subscribe("/husky3/ground_truth/state", 100, &MoveHusky::current_pos3,this);
	sub_pos4 = n3.subscribe("/husky4/ground_truth/state", 100, &MoveHusky::current_pos4,this);
	sub_pos5 = n3.subscribe("/husky5/ground_truth/state", 100, &MoveHusky::current_pos5,this);
	//1 subscriber from Brain1
	sub_brain1 = n1.subscribe("brain1_to_move",1000, &MoveHusky::direction_to_move, this);

	//x1 = 0.0,Y1 = 0.0,z1= 0.0,theta1= 0.0,x2= 0.0,y2= 0.0,z2= 0.0,theta2= 0.0;
	//ini_theta2= 0.0,ini_y2= 0.0,ini_x2= 0.0;
	flag =  0;
	flag2 = 0;
}

MoveHusky::~MoveHusky()
{

}
//float x1 = 0.0,Y1 = 0.0,z1= 0.0,theta1= 0.0,x2= 0.0,y2= 0.0,z2= 0.0,theta2= 0.0;
//float ini_theta2= 0.0,ini_y2= 0.0,ini_x2= 0.0;
//char dir;
//int flag = 0;
//geometry_msgs::Twist vel1,vel2;

void MoveHusky::current_pos1(const nav_msgs::Odometry::ConstPtr& msg)
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
  x1 =      msg->pose.pose.position.x;
  Y1 =      msg->pose.pose.position.y;
  z1 = 	   msg->pose.pose.position.z ;
  theta1 = msg->pose.pose.orientation.z;
  std::cout<<"POS OF ROBO 1 : "<<"x1: "<<x1<<" "<<"Y1 : "<<Y1<<" "<<" theta1: "<<theta1<<endl;
}  

void MoveHusky::current_pos2(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x2 =      msg->pose.pose.position.x ;
  y2 =      msg->pose.pose.position.y ;
  z2 = 	   msg->pose.pose.position.z ;
  theta2 = msg->pose.pose.orientation.z;
  if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 2 : "<<"x2 : "<<ini_x2<<" "<<"y2: "<<ini_y2<<" "<<"theta2: "<<" "<<ini_theta2<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 1 and 2: "<<"X axis : "<<x1 - ini_x2<<"  Y axis : "<<Y1 - ini_y2<<endl;
}  

void MoveHusky::current_pos3(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x3 =      msg->pose.pose.position.x ;
  y3 =      msg->pose.pose.position.y ;
  z3 = 	   msg->pose.pose.position.z ;
  theta3 = msg->pose.pose.orientation.z;
  if(flag2 <= 0){
  	ini_theta3 = theta3;
  	ini_y3 = y3;
  	ini_x3 = x3;
  	flag2++;}
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 3 : "<<"x3 : "<<ini_x3<<" "<<"y3: "<<ini_y3<<" "<<"theta3: "<<" "<<ini_theta3<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 2 and 3: "<<"X axis : "<<ini_x2 - ini_x3<<"  Y axis : "<<ini_y2 - ini_y3<<endl;
}  

void MoveHusky::current_pos4(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x4 =      msg->pose.pose.position.x ;
  y4 =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta4 = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 4 : "<<"x4 : "<<x4<<" "<<"y4: "<<y4<<" "<<"theta4: "<<" "<<theta4<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 1 and 4: "<<"X axis : "<<x1 - x4<<"  Y axis : "<<Y1 - y4<<endl;
}

void MoveHusky::current_pos5(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x5 =      msg->pose.pose.position.x ;
  y5 =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta5 = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 5 : "<<"x5 : "<<x5<<" "<<"y5: "<<y5<<" "<<"theta5: "<<" "<<theta5<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 4 and 5: "<<"X axis : "<<x4 - x5<<"  Y axis : "<<y4 - y5<<endl;
}

void MoveHusky::direction_to_move(const std_msgs::Char::ConstPtr& msg)
{
	dir = msg->data;
	std::cout<<"heard this from Brain1: "<<dir<<endl;
}

void MoveHusky::move1()
{
		std::cout<<"entered MOVE1"<<endl;
		
		dir = 's';
		std::cout<<"value of dir is : "<<dir<<endl;
		if(dir == 'w'){ //FORWARD
			vel1.linear.x  =  0.1;
			vel1.angular.z =  0.0;
			std::cout<<"Moving Forward"<<endl;
			// we need to make flag zero for any change in the coordinates of x1,y1
			flag = 0; 
			ros::Duration(0.1);
		}else if(dir == 'a'){ // LEFT TURN
			vel1.linear.x  =   0.0;
			vel1.angular.z =  -0.5;
			flag = 0;
			ros::Duration(0.1);			
		}else if(dir == 'd'){           // RIGHT
			vel1.linear.x  =  0.0;
			vel1.angular.z =  0.5;
			flag = 0;
			ros::Duration(0.1);			

		}else if(dir == 's'){				//BACK
			vel1.linear.x  =  -0.3;
			vel1.angular.z =   0.0;
			flag = 0;
			ros::Duration(0.1);			
		}else{  			// STOP
			vel1.linear.x  =   0.0;
			vel1.angular.z =   0.0;

			ros::Duration(0.1);						
		}
		//return vel1;
		vel1_pub.publish(vel1);
		ros::Duration(0.1);
		//return;
		
		std::cout<<"=================================================="<<endl;
}

void MoveHusky::move2()
{
	std::cout<<"Enetered MOVE2"<<endl;
	
	
	//vel2_pub.publish(vel2);
	//ros::Duration(0.2);
	/*while(fabs(theta2*90 - (1/2)*(225.0 - std::atan2(ini_y2,ini_x2) - std::atan2(Y1,x1))) > 0.1){
		//assign angular to 2
		std::cout<<"in while loop 1"<<endl;
		vel2.angular.z = 0.5;		
		//vel2_pub.publish(vel2);
		return vel2;
		
	}

	while(fabs((y2 + x2) - (Y1 + x1)) < 0.1){ //equation of line : y = -x + y1 + x1. So new x2,y2 will lie on this
		//assign linear x to 2
		std::cout<<"in while loop 2"<<endl;
		vel2.linear.x = 1.0;		
		//vel2_pub.publish(vel2);
	}*/
	//vel2.angular.z = 0.02*(std::atan2((Y1 - y2),(x1 - x2)));
	//vel2.linear.x = 0.1*(std::sqrt(std::pow(Y1 - ini_y2,2) + std::pow(x1 - ini_x2,2))); //taking bot2 at 5m distance
	flag2 = 0;
	vel2.linear.x = 0.15*(x1 - 5 - ini_x2); //moving 5m from robo 2x
	if(vel2.linear.x > 0.0 && vel2.linear.x < 0.1)
		vel2.linear.x = 0.1;
	else if(vel2.linear.x < 0.0 && vel2.linear.x > -0.1) 
		vel2.linear.x = -0.1;
	else if(vel2.linear.x == 0.0){
		if(dir == 'w')
			vel2.linear.x = 0.1;
		else if(dir == 's')
			vel2.linear.x = -0.1;		
	}
	vel2_pub.publish(vel2);
	
	ros::Duration(0.1);
	
	//return vel2;																						
	std::cout<<"++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
}

void MoveHusky::move3()
{
	std::cout<<"Entered MOVE3"<<endl;

	vel3.linear.x = 0.15*(ini_x2 - 5 - ini_x3); //moving 5m from robo 2
	if(vel3.linear.x > 0.0 && vel3.linear.x < 0.1)
		vel3.linear.x = 0.1;
	else if(vel3.linear.x < 0.0 && vel3.linear.x > -0.1) 
		vel3.linear.x = -0.1;
	else if(vel3.linear.x == 0.0){
		if(dir == 'w')
			vel3.linear.x = 0.1;
		else if(dir == 's')
			vel3.linear.x = -0.1;		
	}
	

	vel3_pub.publish(vel3);
	ros::Duration(0.1);

	std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
}

void MoveHusky::move4()
{
	std::cout<<"Entered MOVE4"<<endl;

	vel4.linear.x = 0.15*(x1 + 5 - x4); //moving ahead 5m from robo 1
	if(vel4.linear.x > 0.0 && vel4.linear.x < 0.1)
		vel4.linear.x = 0.1;
	else if(vel4.linear.x < 0.0 && vel4.linear.x > -0.1) 
		vel4.linear.x = -0.1;
	else if(vel4.linear.x == 0.0){
		if(dir == 'w')
			vel4.linear.x = 0.1;
		else if(dir == 's')
			vel4.linear.x = -0.1;		
	}

	vel4_pub.publish(vel4);
	ros::Duration(0.1);
	std::cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
}

void MoveHusky::move5()
{
	std::cout<<"Entered MOVE5"<<endl;

	vel5.linear.x = 0.15*(x4 + 5 - x5); //moving 5m from robo 4
	if(vel5.linear.x > 0.0 && vel5.linear.x < 0.1)
		vel5.linear.x = 0.1;
	else if(vel5.linear.x < 0.0 && vel5.linear.x > -0.1) 
		vel5.linear.x = -0.1;
	else if(vel5.linear.x == 0.0){
		if(dir == 'w')
			vel5.linear.x = 0.1;
		else if(dir == 's')
			vel5.linear.x = -0.1;		
	}

	vel5_pub.publish(vel5);
	ros::Duration(0.1);
	std::cout<<"************************************************"<<endl;
}


int main(int argc, char **argv){

	ros::init(argc,argv,"Mover");

	MoveHusky h1;
	
	ros::Rate loop_rate(10);
	//ros::MultiThreadedSpinner spinner(4); // Use 4 threads

	//ros::Time ros_time;
	geometry_msgs::Twist v1,v2,v3;
	//We'll move 1 and 2 will move accordingly
	while(ros::ok()){

		std::cout<<"in ros ok"<<endl;

		h1.move1();
		h1.move2();
		h1.move3();
		h1.move4();
		h1.move5();

		//h1.vel2.linear.x = -0.5;
		//h1.vel2.angular.z = -0.1;

		//h1.vel1.linear.x  =  0.5;
		//h1.vel1.angular.z =  0.1;


		//std::cout<<"velocity of robo 1 is : "<<v1.linear.x<<" "<<v1.angular.z<<endl;
		//std::cout<<"velocity of robo 2 is : "<<v2.linear.x<<" "<<v2.angular.z<<endl;

		//h1.vel1_pub.publish(v1);
		//ros::Duration(0.1);
		//h1.vel2_pub.publish(v2);
		//ros::Duration(0.1);
		//spinner.spin(); // spin() will not return until the node has been shutdown
		ros::spinOnce();
		loop_rate.sleep();

	}

	return 0;
}
