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
#include "husky_test_marker.h"


using namespace std;

MoveHusky::MoveHusky()
{
	vel1_pub = n1.advertise<geometry_msgs::Twist>("/husky1/husky_velocity_controller/cmd_vel", 10);
	vel2_pub = n1.advertise<geometry_msgs::Twist>("/husky2/husky_velocity_controller/cmd_vel", 10);
	vel3_pub = n1.advertise<geometry_msgs::Twist>("/husky3/husky_velocity_controller/cmd_vel", 10);
	vel4_pub = n2.advertise<geometry_msgs::Twist>("/husky4/husky_velocity_controller/cmd_vel", 10);
	vel5_pub = n2.advertise<geometry_msgs::Twist>("/husky5/husky_velocity_controller/cmd_vel", 10);	
	vel6_pub = n2.advertise<geometry_msgs::Twist>("/husky6/husky_velocity_controller/cmd_vel", 10);	
	vel7_pub = n3.advertise<geometry_msgs::Twist>("/husky7/husky_velocity_controller/cmd_vel", 10);	
	vel8_pub = n3.advertise<geometry_msgs::Twist>("/husky8/husky_velocity_controller/cmd_vel", 10);	
	vel9_pub = n3.advertise<geometry_msgs::Twist>("/husky9/husky_velocity_controller/cmd_vel", 10);	

	//2 subscribers for current position : ODOMbrain1_to_move
	sub_pos1 = n1.subscribe("/husky1/ground_truth/state", 100, &MoveHusky::current_pos1, this);
	sub_pos2 = n1.subscribe("/husky2/ground_truth/state", 100, &MoveHusky::current_pos2,this);
	sub_pos3 = n1.subscribe("/husky3/ground_truth/state", 100, &MoveHusky::current_pos3,this);
	sub_pos4 = n2.subscribe("/husky4/ground_truth/state", 100, &MoveHusky::current_pos4,this);
	sub_pos5 = n2.subscribe("/husky5/ground_truth/state", 100, &MoveHusky::current_pos5,this);
	sub_pos6 = n2.subscribe("/husky6/ground_truth/state", 100, &MoveHusky::current_pos6,this);
	sub_pos7 = n3.subscribe("/husky7/ground_truth/state", 100, &MoveHusky::current_pos7,this);
	sub_pos8 = n3.subscribe("/husky8/ground_truth/state", 100, &MoveHusky::current_pos8,this);
	sub_pos9 = n3.subscribe("/husky9/ground_truth/state", 100, &MoveHusky::current_pos9,this);
	//1 subscriber from Brain1
	sub_brain1 = n1.subscribe("brain1_to_move",1000, &MoveHusky::direction_to_move, this);

	marker_pub = n1.advertise<visualization_msgs::MarkerArray>("visualization_marker_array_mover", 1);
	//x1 = 0.0,Y1 = 0.0,z1= 0.0,theta1= 0.0,x2= 0.0,y2= 0.0,z2= 0.0,theta2= 0.0;
	//ini_theta2= 0.0,ini_y2= 0.0,ini_x2= 0.0;
	flag =  0;
	flag2 = 0;
	uint32_t shape = visualization_msgs::Marker::CUBE;

	M.markers.resize(9);

		for(int i=0;i<9;i++){
        	
        	M.markers[i].header.frame_id = "/my_frame_array";
        	M.markers[i].header.stamp = ros::Time::now();
        
        	M.markers[i].ns = "array_mover";
	        M.markers[i].id = i;
	        
	        M.markers[i].type = shape;
	        
	        M.markers[i].action = visualization_msgs::Marker::ADD; 


	    M.markers[i].pose.position.x = 2*i;
	    M.markers[i].pose.position.y = 0;    
        M.markers[i].pose.position.z = 0;

        M.markers[i].pose.orientation.x = 0.0;
        M.markers[i].pose.orientation.y = 0.0;
        M.markers[i].pose.orientation.z = 0.0;
        M.markers[i].pose.orientation.w = 1.0;
        
        M.markers[i].scale.x = 1.0;
        M.markers[i].scale.y = 1.0;
        M.markers[i].scale.z = 1.0;
        
        M.markers[i].color.r = 0.0f;
        M.markers[i].color.g = 1.0f;
        M.markers[i].color.b = 0.0f;
        M.markers[i].color.a = 1.0;
   
        M.markers[i].lifetime = ros::Duration();

    	}
}

MoveHusky::~MoveHusky()
{

}

void MoveHusky::publish_marker()
{
	marker_pub.publish(M);
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
  x[0] =      msg->pose.pose.position.x;
  y[0] =      msg->pose.pose.position.y;
  z[0] = 	   msg->pose.pose.position.z ;
  theta[0] = msg->pose.pose.orientation.z;
  std::cout<<"POS OF ROBO 1 : "<<"x1: "<<x[0]<<" "<<"Y1 : "<<y[0]<<" "<<" theta1: "<<theta[0]<<endl;

  M.markers[0].pose.position.x = x[0];
  //M.markers[0].pose.position.y = Y1;
  M.markers[0].pose.position.y = y[0];
}  

void MoveHusky::current_pos2(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[1] =      msg->pose.pose.position.x ;
  y[1] =      msg->pose.pose.position.y ;
  z[1] = 	   msg->pose.pose.position.z ;
  theta[1] = msg->pose.pose.orientation.z;
  if(flag <= 0){
  	ini_theta2 = theta[1];
  	ini_y2 = y[1];
  	ini_x2 = x[1];
  	flag++;}
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 2 : "<<"x2 : "<<ini_x2<<" "<<"y2: "<<ini_y2<<" "<<"theta2: "<<" "<<ini_theta2<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 1 and 2: "<<"X axis : "<<x[0] - ini_x2<<"  Y axis : "<<y[0] - ini_y2<<endl;
  M.markers[1].pose.position.x = x[1];
  M.markers[1].pose.position.y = y[1];  	
}  

void MoveHusky::current_pos3(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[2] =      msg->pose.pose.position.x ;
  y[2] =      msg->pose.pose.position.y ;
  z[2] = 	   msg->pose.pose.position.z ;
  theta[2] = msg->pose.pose.orientation.z;
  if(flag2 <= 0){
  	ini_theta3 = theta[2];
  	ini_y3 = y[2];
  	ini_x3 = x[2];
  	flag2++;}
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 3 : "<<"x3 : "<<ini_x3<<" "<<"y3: "<<ini_y3<<" "<<"theta3: "<<" "<<ini_theta3<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 2 and 3: "<<"X axis : "<<ini_x2 - ini_x3<<"  Y axis : "<<ini_y2 - ini_y3<<endl;

  M.markers[2].pose.position.x = x[2];
  M.markers[2].pose.position.y = y[2];  	
}  

void MoveHusky::current_pos4(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[3] =      msg->pose.pose.position.x ;
  y[3] =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta[3] = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 4 : "<<"x4 : "<<x[3]<<" "<<"y4: "<<y[3]<<" "<<"theta4: "<<" "<<theta[3]<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 1 and 4: "<<"X axis : "<<x[0] - x[3]<<"  Y axis : "<<y[0] - y[3]<<endl;
  M.markers[3].pose.position.x = x[3];
  M.markers[3].pose.position.y = y[3];

}

void MoveHusky::current_pos5(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[4] =      msg->pose.pose.position.x ;
  y[4] =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta[4] = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 5 : "<<"x5 : "<<x[4]<<" "<<"y5: "<<y[4]<<" "<<"theta5: "<<" "<<theta[4]<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 4 and 5: "<<"X axis : "<<x[3] - x[4]<<"  Y axis : "<<y[3] - y[4]<<endl;
  M.markers[4].pose.position.x = x[4];
  M.markers[4].pose.position.y = y[4];

}

void MoveHusky::current_pos6(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[5] =      msg->pose.pose.position.x ;
  y[5] =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta[5] = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 6 : "<<"x6 : "<<x[5]<<" "<<"y6: "<<y[5]<<" "<<"theta6: "<<" "<<theta[5]<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 1 and 6: "<<"X axis : "<<x[1] - x[5]<<"  Y axis : "<<y[1] - y[5]<<endl;
  M.markers[5].pose.position.x = x[5];
  M.markers[5].pose.position.y = y[5];

}

void MoveHusky::current_pos7(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[6] =      msg->pose.pose.position.x ;
  y[6] =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta[6] = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 7 : "<<"x7 : "<<x[6]<<" "<<"y7: "<<y[6]<<" "<<"theta7: "<<" "<<theta[6]<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 3 and 7: "<<"X axis : "<<x[2] - x[6]<<"  Y axis : "<<y[2] - y[6]<<endl;
  M.markers[6].pose.position.x = x[6];
  M.markers[6].pose.position.y = y[6];

}

void MoveHusky::current_pos8(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[7] =      msg->pose.pose.position.x ;
  y[7] =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta[7] = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 5 : "<<"x8 : "<<x[7]<<" "<<"y8: "<<y[7]<<" "<<"theta8: "<<" "<<theta[7]<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 3 and 8: "<<"X axis : "<<x[3] - x[7]<<"  Y axis : "<<y[3] - y[7]<<endl;
  M.markers[7].pose.position.x = x[7];
  M.markers[7].pose.position.y = y[7];

}

void MoveHusky::current_pos9(const nav_msgs::Odometry::ConstPtr& msg)
{
  
  x[8] =      msg->pose.pose.position.x ;
  y[8] =      msg->pose.pose.position.y ;
  //z2 = 	   msg->pose.pose.position.z ;
  theta[8] = msg->pose.pose.orientation.z;
  /*if(flag <= 0){
  	ini_theta2 = theta2;
  	ini_y2 = y2;
  	ini_x2 = x2;
  	flag++;}*/
  	//GETTING 2 READING FOR POSITION OF ROBO 2 , SO USING IF TO AVOID SECOND ONE
	std::cout<<"POS OF ROBO 9 : "<<"x9 : "<<x[8]<<" "<<"y9: "<<y[8]<<" "<<"theta9: "<<" "<<theta[8]<<" \n";
  	std::cout<<endl;
  	std::cout<<"DIFFERENCE B/W 4 and 9: "<<"X axis : "<<x[4] - x[8]<<"  Y axis : "<<y[4] - y[8]<<endl;
  M.markers[8].pose.position.x = x[8];
  M.markers[8].pose.position.y = y[8];

}


void MoveHusky::direction_to_move(const std_msgs::Char::ConstPtr& msg)
{
	dir = msg->data;
	std::cout<<"heard this from Brain1: "<<dir<<endl;
}

void MoveHusky::move1()
{
		std::cout<<"entered MOVE1"<<endl;
		
		dir = 'w';
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
	vel2.linear.x = 0.15*(x[0] - 5 - ini_x2); //moving 5m from robo 2x
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

	vel4.linear.x = 0.15*(x[0] + 5 - x[3]); //moving ahead 5m from robo 1
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

	vel5.linear.x = 0.15*(x[3] + 5 - x[6]); //moving 5m from robo 4
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

void MoveHusky::move6()
{
	std::cout<<"Entered MOVE6"<<endl;

	vel6.linear.x = 0.15*(x[5] - 5 - ini_x2); //moving 5m from robo 4
	if(vel6.linear.x > 0.0 && vel6.linear.x < 0.1)
		vel6.linear.x = 0.1;
	else if(vel6.linear.x < 0.0 && vel6.linear.x > -0.1) 
		vel6.linear.x = -0.1;
	else if(vel6.linear.x == 0.0){
		if(dir == 'w')
			vel6.linear.x = 0.1;
		else if(dir == 's')
			vel6.linear.x = -0.1;		
	}

	vel6_pub.publish(vel6);
	ros::Duration(0.1);
	std::cout<<"66666666666666666666666666666666666666666666666666"<<endl;
}

void MoveHusky::move7()
{
	std::cout<<"Entered MOVE7"<<endl;

	vel7.linear.x = 0.15*(x[6] - 5 - ini_x3); //moving 5m from robo 4
	if(vel7.linear.x > 0.0 && vel7.linear.x < 0.1)
		vel7.linear.x = 0.1;
	else if(vel7.linear.x < 0.0 && vel7.linear.x > -0.1) 
		vel7.linear.x = -0.1;
	else if(vel7.linear.x == 0.0){
		if(dir == 'w')
			vel7.linear.x = 0.1;
		else if(dir == 's')
			vel7.linear.x = -0.1;		
	}

	vel7_pub.publish(vel7);
	ros::Duration(0.1);
	std::cout<<"777777777777777777777777777777777777777777777777777"<<endl;
}

void MoveHusky::move8()
{
	std::cout<<"Entered MOVE8"<<endl;

	vel8.linear.x = 0.15*(x[7] - 5 - x[3]); //moving 5m from robo 4
	if(vel8.linear.x > 0.0 && vel8.linear.x < 0.1)
		vel8.linear.x = 0.1;
	else if(vel8.linear.x < 0.0 && vel8.linear.x > -0.1) 
		vel8.linear.x = -0.1;
	else if(vel8.linear.x == 0.0){
		if(dir == 'w')
			vel8.linear.x = 0.1;
		else if(dir == 's')
			vel8.linear.x = -0.1;		
	}

	vel8_pub.publish(vel8);
	ros::Duration(0.1);
	std::cout<<"888888888888888888888888888888888888888888888888888888"<<endl;
}

void MoveHusky::move9()
{
	std::cout<<"Entered MOVE9"<<endl;

	vel9.linear.x = 0.15*(x[8] - 5 - x[4]); //moving 5m from robo 4
	if(vel9.linear.x > 0.0 && vel9.linear.x < 0.1)
		vel9.linear.x = 0.1;
	else if(vel9.linear.x < 0.0 && vel9.linear.x > -0.1) 
		vel9.linear.x = -0.1;
	else if(vel9.linear.x == 0.0){
		if(dir == 'w')
			vel9.linear.x = 0.1;
		else if(dir == 's')
			vel9.linear.x = -0.1;		
	}

	vel9_pub.publish(vel9);
	ros::Duration(0.1);
	std::cout<<"999999999999999999999999999999999999999999999999999"<<endl;
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
		h1.move6();
		h1.move7();
		h1.move8();
		h1.move9();

		h1.publish_marker();
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
