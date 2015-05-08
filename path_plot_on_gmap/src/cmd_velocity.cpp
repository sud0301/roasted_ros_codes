#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>  
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h> 
#include <math.h>
#include <nav_msgs/Path.h>
//nav_msgs::Odometry pose;
geometry_msgs::Twist pos;
geometry_msgs::Twist pos_1;

void pose_callback(const geometry_msgs::Twist::ConstPtr& msg)
{


pos_1.linear.x=msg->linear.x;
pos_1.linear.y=msg->linear.y;
pos_1.linear.z=msg->linear.z;

pos_1.angular.x=msg->angular.x;
pos_1.angular.y=msg->angular.y;
pos_1.angular.z=msg->angular.z;


}

int main(int argc, char **argv)
{

	ros::init(argc, argv, "p3dx_subscriber");

	//pos_1.header.frame_id="/map";

	ros::NodeHandle n;

	ros::Subscriber pose_sub = n.subscribe<geometry_msgs::Twist>("cmd_v",100,&pose_callback);
	ros::Publisher path_pub =  n.advertise<geometry_msgs::Twist>("cmd_velocity",100);

	void pose_callback(const geometry_msgs::Twist::ConstPtr& joy);
	while(ros::ok())
	{
		path_pub.publish(pos_1);
		//ros::Duration(0.1).sleep();
		ros::spinOnce();
	}
}
