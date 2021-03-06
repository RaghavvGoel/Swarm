#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main( int argc, char** argv )
{
  ros::init(argc, argv, "array2");
  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 1);
  //ros::Publisher marker_pub2 = n.advertise<visualization_msgs::Marker>("visualization_marker2", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  float x1 , y1 , x2 , y2;

    visualization_msgs::MarkerArray M;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    M.markers.resize(2);
    M.markers[0].header.frame_id = "/my_frame2";
    M.markers[1].header.frame_id = "/my_frame2";
    M.markers[0].header.stamp = ros::Time::now();
    M.markers[1].header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    M.markers[0].ns = "basic_shapes";
    M.markers[1].ns = "basic_shapes";
    M.markers[0].id = 0;
    M.markers[1].id = 1;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    M.markers[0].type = shape;
    M.markers[1].type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    M.markers[0].action = visualization_msgs::Marker::ADD;
    M.markers[1].action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    M.markers[0].pose.position.x = 2;
    M.markers[0].pose.position.y = 2;
    M.markers[0].pose.position.z = 0;
    M.markers[0].pose.orientation.x = 0.0;
    M.markers[0].pose.orientation.y = 0.0;
    M.markers[0].pose.orientation.z = 0.0;
    M.markers[0].pose.orientation.w = 1.0;

    M.markers[1].pose.position.x = 0;
    M.markers[1].pose.position.y = 0;
    M.markers[1].pose.position.z = 0;
    M.markers[1].pose.orientation.x = 0.0;
    M.markers[1].pose.orientation.y = 0.0;
    M.markers[1].pose.orientation.z = 0.0;
    M.markers[1].pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    M.markers[0].scale.x = 1.0;
    M.markers[0].scale.y = 1.0;
    M.markers[0].scale.z = 1.0;

    M.markers[1].scale.x = 1.0;
    M.markers[1].scale.y = 1.0;
    M.markers[1].scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    M.markers[0].color.r = 0.0f;
    M.markers[0].color.g = 1.0f;
    M.markers[0].color.b = 0.0f;
    M.markers[0].color.a = 1.0;

    M.markers[1].color.r = 0.0f;
    M.markers[1].color.g = 1.0f;
    M.markers[1].color.b = 0.0f;
    M.markers[1].color.a = 1.0;

    M.markers[0].lifetime = ros::Duration();


    M.markers[1].lifetime = ros::Duration();

    x1 = M.markers[0].pose.position.x ;
    y1 = M.markers[0].pose.position.y ;

    x2 = M.markers[1].pose.position.x ;
    y2 = M.markers[1].pose.position.x ;

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
    marker_pub.publish(M);
    //marker_pub2.publish(marker2);

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
    
    M.markers[0].pose.position.x = x1 - 0.1;
    //marker.pose.position.y = y1 + 0.1;
    
    //y1 = marker.pose.position.y;

    M.markers[1].pose.position.x = x2 + 0.1*(x1-x2)/3;

    x1 = M.markers[0].pose.position.x;
    x2 = M.markers[1].pose.position.x;

    std::cout<<"X1: "<<x1<<"  Y1: "<<y1<<endl;
    std::cout<<"X2: "<<x2<<"  Y2: "<<y2<<endl;

    std::cout<<"DIFFERENCE : "<<x1-x2<<endl;

    r.sleep();
  }
  //ros::spin();
  //return 0;
}