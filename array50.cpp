#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main( int argc, char** argv )
{
  ros::init(argc, argv, "array50");
  ros::NodeHandle n;
  ros::Rate r(5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_marker_array50", 1);
  //ros::Publisher marker_pub2 = n.advertise<visualization_msgs::Marker>("visualization_marker2", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  float x[50] , y[50];
    int i=0 , j=0 ,k;
    visualization_msgs::MarkerArray M;
    M.markers.resize(50);
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    //while(j<9){
      //i = j;
      for(i=0;i<50;i++){
        M.markers[i].header.frame_id = "/my_frame50";
        M.markers[i].header.stamp = ros::Time::now();
        
        M.markers[i].ns = "array50";
        
        M.markers[i].id = i;
        
        M.markers[i].type = shape;
        
        M.markers[i].action = visualization_msgs::Marker::ADD;

        
        if(i == 10 || i==19 || i==28 || i==37 || i==46){
          j = j+1;
          k = 0;
        }
          M.markers[i].pose.position.x = 2*j + 1;
        
         // M.markers[i].pose.position.x = 2*(-j) + 1;

        M.markers[i].pose.position.y = (2*(k) - 1) - 5;
        k++;
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

        x[i] = M.markers[i].pose.position.x;
        y[i] = M.markers[i].pose.position.y;
        //i++;
    
  }

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
    
    M.markers[0].pose.position.x = x[0] - 0.1;
    //marker.pose.position.y = y1 + 0.1;
    
    //y1 = marker.pose.position.y;
    for(int i=1;i<50;i++){
      M.markers[i].pose.position.x = x[i] + 0.1*(x[i-1]-x[i])/3;
    }

    for(int i=0;i<50;i++){
      x[i] = M.markers[i].pose.position.x;      
    }

    std::cout<<"X0: "<<x[0]<<"  Y0: "<<y[0]<<endl;
    std::cout<<"X1: "<<x[1]<<"  Y1: "<<y[1]<<endl;

    std::cout<<"DIFFERENCE : "<<x[0]-x[1]<<endl;
    std::cout<<

    r.sleep();
  }
  //ros::spin();
  //return 0;
}