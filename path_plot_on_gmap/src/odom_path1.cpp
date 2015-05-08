#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>  
#include <visualization_msgs/Marker.h>
 

#include <nav_msgs/Path.h>
nav_msgs::Odometry odom;
nav_msgs::Path path;


void odom_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
geometry_msgs::PoseStamped pose;
pose.pose.position.x=msg->pose.pose.position.x;
printf("here\n");
pose.pose.position.y=msg->pose.pose.position.y;
pose.pose.position.z=msg->pose.pose.position.z;
pose.pose.orientation.x=msg->pose.pose.orientation.x;
pose.pose.orientation.y=msg->pose.pose.orientation.y;
pose.pose.orientation.z=msg->pose.pose.orientation.z;
pose.pose.orientation.w=msg->pose.pose.orientation.w;
path.poses.push_back(pose);

}

int main(int argc, char **argv)
{

 ros::init(argc, argv, "p3dx_subscriber");

path.header.frame_id="/odom";

ros::NodeHandle n;
ros::Subscriber odom_sub=n.subscribe<nav_msgs::Odometry>("pose",10,&odom_callback);
ros::Publisher path_pub=n.advertise<nav_msgs::Path>("Path1",10);

void odom_callback(const nav_msgs::Odometry::ConstPtr& joy);

while(ros::ok())
{
path_pub.publish(path);

ros::Duration(0.1).sleep();
ros::spinOnce();
}



}
//}
