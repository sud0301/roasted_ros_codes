#include <ros/ros.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
//#include <sstream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <std_msgs/Header.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/MapMetaData.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>

using namespace cv;
using namespace std;

ros::Subscriber sub1;   
ros::Subscriber sub2;
nav_msgs::Odometry pose;

void pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
cout << "X "<<msg->pose.pose.position.x<< "	"<<"Y	"<<msg->pose.pose.position.y<<endl;
/*geometry_msgs::PoseStamped pose;
pose.pose.position.x=msg->pose.pose.position.x;
printf("here\n");
pose.pose.position.y=msg->pose.pose.position.y;
pose.pose.position.z=msg->pose.pose.position.z;
pose.pose.orientation.x=msg->pose.pose.orientation.x;
pose.pose.orientation.y=msg->pose.pose.orientation.y;
pose.pose.orientation.z=msg->pose.pose.orientation.z;
pose.pose.orientation.w=msg->pose.pose.orientation.w;}*/
}
//void chatterCallback2 (const nav_msgs::OccupancyGrid& point2)
//{}

int main(int  argc, char** argv)
{
	ros::init(argc,argv,"new_front_explore");
	ros::NodeHandle n;

	sub1 =n.subscribe<nav_msgs::Odometry>("/odom",10,&pose_callback);
//	sub2 =n.subscribe ("/map",1,chatterCallback2);
	ros::spin();

}

