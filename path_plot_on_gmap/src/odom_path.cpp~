#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>  
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
 
#include <math.h>
#include <nav_msgs/Path.h>
//nav_msgs::Odometry pose;
geometry_msgs::PoseStamped pose_1;
nav_msgs::Odometry odom_1;
//nav_msgs::Path path;


//int dis=0;
float x_1=0; float x_diff=0; float x=0;
float y_1=0; float y_diff=0; float y=0;
float dis=0; float distance=0;
int iter=1;
float error=0; float error_sum=0; float error_avg=0;


//void pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
void odom_callback(const nav_msgs::Odometry::ConstPtr& msg)
{

	
	odom_1.pose.pose.position.x=msg->pose.pose.position.x;
	odom_1.pose.pose.position.y=msg->pose.pose.position.y;
	odom_1.pose.pose.position.z=msg->pose.pose.position.z;
	odom_1.pose.pose.orientation.x=msg->pose.pose.orientation.x;
	odom_1.pose.pose.orientation.y=msg->pose.pose.orientation.y;
	odom_1.pose.pose.orientation.z=msg->pose.pose.orientation.z;
	odom_1.pose.pose.orientation.w=msg->pose.pose.orientation.w;
	

}

void pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{

	//geometry_msgs::PoseStamped pose;
	x=msg->pose.pose.position.x;
	y=msg->pose.pose.position.y;
	
	x_diff=x-x_1;
	y_diff=y-y_1;
	
	dis=sqrt(x_diff*x_diff+y_diff*y_diff);
	distance=distance +dis;
	
	printf("distance: %f",distance);
	pose_1.pose.position.x=msg->pose.pose.position.x;
	printf("here\n");
	pose_1.pose.position.y=msg->pose.pose.position.y;
	pose_1.pose.position.z=msg->pose.pose.position.z;
	pose_1.pose.orientation.x=msg->pose.pose.orientation.x;
	pose_1.pose.orientation.y=msg->pose.pose.orientation.y;
	pose_1.pose.orientation.z=msg->pose.pose.orientation.z;
	pose_1.pose.orientation.w=msg->pose.pose.orientation.w;
	
	error= sqrt((odom_1.pose.pose.position.x-pose_1.pose.position.x)*(odom_1.pose.pose.position.x-pose_1.pose.position.x) + (odom_1.pose.pose.position.y-pose_1.pose.position.y)*(odom_1.pose.pose.position.y-pose_1.pose.position.y));
	error_sum=error_sum+error;
	error_avg=error_sum/iter;

	printf("error_avg: %f 	iteration:%d ",error_avg, iter );
	
	x_1=msg->pose.pose.position.x;
	y_1=msg->pose.pose.position.y;
	iter=iter+1;	
	

}

int main(int argc, char **argv)
{

ros::init(argc, argv, "p3dx_subscriber");
//path.header.frame_id="/map";
ros::NodeHandle n;

//ros::Subscriber pose_sub=n.subscribe<nav_msgs::Odometry>("amcl_pose",10,&pose_callback);
ros::Subscriber pose_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",10,&pose_callback);
ros::Subscriber odom_sub = n.subscribe<nav_msgs::Odometry>("odom",10,&odom_callback);
//ros::Publisher path_pub =  n.advertise<nav_msgs::Path>("Path",10);

//void pose_callback(const nav_msgs::Odometry::ConstPtr& joy);

void pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& joy);
void odom_callback(const nav_msgs::Odometry::ConstPtr& roy);
while(ros::ok())
	{
		//path_pub.publish(path);
		ros::Duration(0.1).sleep();
		ros::spinOnce();
	}



}
//}
