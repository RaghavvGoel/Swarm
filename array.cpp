#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

using namespace std;
main (int argc, char** argv)
{

visualization_msgs::Marker marker;
visualization_msgs::MarkerArray marker_array_msg;

  // Initialize ROS
  ros::init (argc, argv, "pcl_tabletop");
  ros::NodeHandle nh;

  ros::Publisher pub_marker = nh.advertise<visualization_msgs::MarkerArray>("normals_marker_array", 100);

  ros::Rate loop_rate(10);
//pub_marker1 = nh.advertise<visualization_msgs::Marker>("normals_marker", 0);
/*while(1)
{
	
marker.header.frame_id = "base_link";
marker.header.stamp = ros::Time();
marker.ns = "my_namespace";
marker.id = 120;
marker.type = visualization_msgs::Marker::SPHERE;
marker.action = visualization_msgs::Marker::ADD;
marker.pose.position.x = 1;
marker.pose.position.y = 1;
marker.pose.position.z = 1;
marker.pose.orientation.x = 0.0;
marker.pose.orientation.y = 0.0;
marker.pose.orientation.z = 0.0;
marker.pose.orientation.w = 1.0;
marker.scale.x = 1;
marker.scale.y = 0.1;
marker.scale.z = 0.1;
marker.color.a = 1.0;
marker.color.r = 1.0;
marker.color.g = 0.0;
marker.color.b = 0.0;

//pub_marker.publish(marker_array_msg);

pub_marker1.publish(marker);
}*/

marker_array_msg.markers.resize(5);//final->width * final->height);
for ( int i = 0; i < 5; i++)
{
    marker_array_msg.markers[i].header.frame_id = "my_frame";
    marker_array_msg.markers[i].header.stamp = ros::Time();
    marker_array_msg.markers[i].ns = "my_namespace";
    marker_array_msg.markers[i].id = i;
    marker_array_msg.markers[i].type = visualization_msgs::Marker::SPHERE;
    marker_array_msg.markers[i].action = visualization_msgs::Marker::ADD;
    marker_array_msg.markers[i].pose.position.x = i+5;
    marker_array_msg.markers[i].pose.position.y = 5+i;
    marker_array_msg.markers[i].pose.position.z = 0;
    marker_array_msg.markers[i].pose.orientation.x = 0.0;
    marker_array_msg.markers[i].pose.orientation.y = 0.0;
    marker_array_msg.markers[i].pose.orientation.z = 0.0;
    marker_array_msg.markers[i].pose.orientation.w = 1.0;
    marker_array_msg.markers[i].scale.x = 1;
    marker_array_msg.markers[i].scale.y = 0.1;
    marker_array_msg.markers[i].scale.z = 0.1;
    marker_array_msg.markers[i].color.a = 1.0;
    marker_array_msg.markers[i].color.r = 0.0;
    marker_array_msg.markers[i].lifetime = ros::Duration();
    if (i == 0)
    {
        marker_array_msg.markers[i].color.g = 0.1;
    }
    else
    {
        marker_array_msg.markers[i].color.g = i * 0.15;
    }
    marker_array_msg.markers[i].color.b = 0.0;

   //m.lifetime = ros::Duration();

     //marker_array_msg.markers.push_back(mark);
}
float ini_x = marker_array_msg.markers[0].pose.position.x;
float ini_y = marker_array_msg.markers[0].pose.position.y;
while(1)
{
	//for( int i=0;i<5;i++)
	//	marker_array_msg.markers[i].header.stamp = ros::Time::now();
	//std::cout<<"yo";	
 pub_marker.publish(marker_array_msg);
     marker_array_msg.markers[0].pose.position.x = ini_x + 0.5;
    marker_array_msg.markers[0].pose.position.y = ini_y + 0.5;
    ini_y = marker_array_msg.markers[0].pose.position.y;
    ini_x = marker_array_msg.markers[0].pose.position.x;
    marker_array_msg.markers[0].lifetime = ros::Duration();


 //loop_rate.sleep();
 
}
	ros::spin();
	//return 0;
  // Spin
  
}