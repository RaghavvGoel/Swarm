#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes0");
  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker0", 1);
  ros::Publisher marker_pub2 = n.advertise<visualization_msgs::Marker>("visualization_marker2", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  float x1 , y1 , x2 , y2;

    visualization_msgs::Marker marker,marker2;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/my_frame0";
    marker2.header.frame_id = "/my_frame0";
    marker.header.stamp = ros::Time::now();
    marker2.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker2.ns = "basic_shapes";
    marker.id = 0;
    marker2.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
    marker2.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
    marker2.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 2;
    marker.pose.position.y = 2;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker2.pose.position.x = 0;
    marker2.pose.position.y = 0;
    marker2.pose.position.z = 0;
    marker2.pose.orientation.x = 0.0;
    marker2.pose.orientation.y = 0.0;
    marker2.pose.orientation.z = 0.0;
    marker2.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    marker2.scale.x = 1.0;
    marker2.scale.y = 1.0;
    marker2.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker2.color.r = 0.0f;
    marker2.color.g = 1.0f;
    marker2.color.b = 0.0f;
    marker2.color.a = 1.0;

    marker.lifetime = ros::Duration();


    marker2.lifetime = ros::Duration();

    x1 = marker.pose.position.x ;
    y1 = marker.pose.position.y ;

    x2 = marker2.pose.position.x ;
    y2 = marker2.pose.position.x ;

  while (ros::ok())
  {
    //std::cout<<"in while loop"<<endl;

    // Publish the marker
/*    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }    */
    marker_pub.publish(marker);
    marker_pub2.publish(marker2);

    // Cycle between different shapes
/*    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }*/
    //ROS_INFO("oyoyo");
    std::cout<<"yolo"<<endl;
    
    marker.pose.position.x = x1 - 0.1;
    //marker.pose.position.y = y1 + 0.1;
    
    //y1 = marker.pose.position.y;

    marker2.pose.position.x = x2 + 0.1*(x1-x2)/3;

    x1 = marker.pose.position.x;
    x2 = marker2.pose.position.x;

    std::cout<<"X1: "<<x1<<"  Y1: "<<y1<<endl;
    std::cout<<"X2: "<<x2<<"  Y2: "<<y2<<endl;

    std::cout<<"DIFFERENCE : "<<x1-x2<<endl;

    r.sleep();
  }
  //ros::spin();
  //return 0;
}