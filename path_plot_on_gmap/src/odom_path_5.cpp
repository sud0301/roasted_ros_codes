#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>  
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
 
#include <math.h>
#include <nav_msgs/Path.h>
//nav_msgs::Odometry pose;
geometry_msgs::PoseWithCovarianceStamped pose;
nav_msgs::Path path;
/*visualization_msgs::Marker marker1;
visualization_msgs::Marker marker2;
visualization_msgs::Marker marker3;
visualization_msgs::Marker marker4;
visualization_msgs::Marker marker5;
visualization_msgs::Marker marker6;
visualization_msgs::Marker marker7;
visualization_msgs::Marker marker8;
visualization_msgs::Marker marker9;
visualization_msgs::Marker marker10;
visualization_msgs::Marker marker11;
visualization_msgs::Marker marker12;
visualization_msgs::Marker marker_o;
visualization_msgs::Marker markerq1;
visualization_msgs::Marker markerq2;
visualization_msgs::Marker markerb1;
visualization_msgs::Marker markerb2;*/

//int dis=0;
float x_1=0; float x_diff=0; float x=0;
float y_1=0; float y_diff=0; float y=0;
float dis=0; float distance=0;



//void pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
void pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{

geometry_msgs::PoseStamped pose;
x=msg->pose.pose.position.x;
y=msg->pose.pose.position.y;

x_diff=x-x_1;
y_diff=y-y_1;

dis=sqrt(x_diff*x_diff+y_diff*y_diff);
distance=distance +dis;

printf("distance: %f",distance);
pose.pose.position.x=msg->pose.pose.position.x;
printf("here\n");
pose.pose.position.y=msg->pose.pose.position.y;
pose.pose.position.z=msg->pose.pose.position.z;
pose.pose.orientation.x=msg->pose.pose.orientation.x;
pose.pose.orientation.y=msg->pose.pose.orientation.y;
pose.pose.orientation.z=msg->pose.pose.orientation.z;
pose.pose.orientation.w=msg->pose.pose.orientation.w;
path.poses.push_back(pose);

x_1=msg->pose.pose.position.x;
y_1=msg->pose.pose.position.y;
/*
marker1.ns = "my_namespace1"; 			// Mug
marker1.id = 0;
marker1.type = visualization_msgs::Marker::CUBE;
marker1.action = visualization_msgs::Marker::ADD;
marker1.pose.position.x = 0.5;
marker1.pose.position.y = 2.5;
marker1.pose.position.z = 0.2;
marker1.pose.orientation.x = 0.0;
marker1.pose.orientation.y = 0.0;
marker1.pose.orientation.z = 0.0;
marker1.pose.orientation.w = 1.0;
marker1.scale.x = 0.2;
marker1.scale.y = 0.2;
marker1.scale.z = 0.2;
marker1.color.a = 1.0;
marker1.color.r = 1.0;
marker1.color.g = 0.0;
marker1.color.b = 0.0;

marker_o.ns = "my_namespace_origin";
marker_o.id = 0;
marker_o.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
marker_o.action = visualization_msgs::Marker::ADD;
marker_o.text="Origin";
marker_o.pose.position.z = 0.2;
marker_o.pose.orientation.x = 0.0;
marker_o.pose.orientation.y = 0.0;
marker_o.pose.orientation.z = 0.0;
marker_o.pose.orientation.w = 1.0;
marker_o.scale.x = 0.4;
marker_o.scale.y = 0.4;
marker_o.scale.z = 0.4;
marker_o.color.a = 1.0;
marker_o.color.r = 0.0;
marker_o.color.g = 0.0;
marker_o.color.b = 0.0;

markerq1.ns = "my_namespace_q1"; //Query Red-1 
markerq1.id = 0;
markerq1.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
markerq1.action = visualization_msgs::Marker::ADD;
markerq1.pose.position.x = 5.3;
markerq1.pose.position.y = 2.2;
markerq1.text="Q1";
markerq1.pose.position.z = 0.1;
markerq1.pose.orientation.x = 0.0;
markerq1.pose.orientation.y = 0.0;
markerq1.pose.orientation.z = 0.0;
markerq1.pose.orientation.w = 1.0;
markerq1.scale.x = 0.4;
markerq1.scale.y = 0.4;
markerq1.scale.z = 0.4;
markerq1.color.a = 1.0;
markerq1.color.r = 0.0;
markerq1.color.g = 0.0;
markerq1.color.b = 0.0;

marker2.ns = "my_namespace2";		//orange_cup
marker2.id = 0;
marker2.type = visualization_msgs::Marker::CYLINDER;
marker2.action = visualization_msgs::Marker::ADD;
marker2.pose.position.x = 5.0;
marker2.pose.position.y = 2.0;
marker2.pose.position.z = 0.1;
marker2.pose.orientation.x = 0.7;
marker2.pose.orientation.y = 0.3;
marker2.pose.orientation.z = 0.0;
marker2.pose.orientation.w = 0.7;
marker2.scale.x = 0.2;
marker2.scale.y = 0.2;
marker2.scale.z = 0.5;
marker2.color.a = 1.0;
marker2.color.r = 0.8;
marker2.color.g = 0.2;
marker2.color.b = 0.6;

markerq2.ns = "my_namespace_q2";
markerq2.id = 0;
markerq2.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
markerq2.action = visualization_msgs::Marker::ADD;
markerq2.pose.position.x = 5.8;
markerq2.pose.position.y =-0.2;
markerq2.text="Q2";
markerq2.pose.position.z = 0.1;
markerq2.pose.orientation.x = 0.0;
markerq2.pose.orientation.y = 0.0;
markerq2.pose.orientation.z = 0.0;
markerq2.pose.orientation.w = 1.0;
markerq2.scale.x = 0.4;
markerq2.scale.y = 0.4;
markerq2.scale.z = 0.4;
markerq2.color.a = 1.0;
markerq2.color.r = 0.0;
markerq2.color.g = 0.0;
markerq2.color.b = 0.0;

marker7.ns = "my_namespace7";   //shampoo
marker7.id = 0;
marker7.type = visualization_msgs::Marker::CUBE;
marker7.action = visualization_msgs::Marker::ADD;
marker7.pose.position.x = 5.5;
marker7.pose.position.y = -0.2;
marker7.pose.position.z = 0.05;
marker7.pose.orientation.x = 0.0;
marker7.pose.orientation.y = 0.0;
marker7.pose.orientation.z = 0.0;
marker7.pose.orientation.w = 1.0;
marker7.scale.x = 0.25;
marker7.scale.y = 0.25;
marker7.scale.z = 0.1;
marker7.color.a = 1.0;
marker7.color.r = 0.1;
marker7.color.g = 0.5;
marker7.color.b = 0.6;




markerb1.ns = "my_namespace_b1"; //Query B1
markerb1.id = 0;
markerb1.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
markerb1.action = visualization_msgs::Marker::ADD;
markerb1.pose.position.x = 6.4;
markerb1.pose.position.y =-2.0;
markerb1.text="B1";
markerb1.pose.position.z = 0.1;
markerb1.pose.orientation.x = 0.0;
markerb1.pose.orientation.y = 0.0;
markerb1.pose.orientation.z = 0.0;
markerb1.pose.orientation.w = 1.0;
markerb1.scale.x = 0.4;
markerb1.scale.y = 0.4;
markerb1.scale.z = 0.4;
markerb1.color.a = 1.0;
markerb1.color.r = 0.0;
markerb1.color.g = 0.0;
markerb1.color.b = 0.0;


marker3.ns = "my_namespace3";
marker3.id = 0;
marker3.type = visualization_msgs::Marker::SPHERE;
marker3.action = visualization_msgs::Marker::ADD;
marker3.pose.position.x = 6.2;
marker3.pose.position.y = -2.0;
marker3.pose.position.z = 0.15;
marker3.pose.orientation.x = 0.7;
marker3.pose.orientation.y = 0.0;
marker3.pose.orientation.z = 0.0;
marker3.pose.orientation.w = 1.0;
marker3.scale.x = 0.2;
marker3.scale.y = 0.4;
marker3.scale.z = 0.2;
marker3.color.a = 1.0;
marker3.color.r = 0.1;
marker3.color.g = 1.0;
marker3.color.b = 0.5;


markerb2.ns = "my_namespace_b2";
markerb2.id = 0;
markerb2.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
markerb2.action = visualization_msgs::Marker::ADD;
markerb2.pose.position.x = 8.9;
markerb2.pose.position.y =-0.8;
markerb2.text="B2";
markerb2.pose.position.z = 0.1;
markerb2.pose.orientation.x = 0.0;
markerb2.pose.orientation.y = 0.0;
markerb2.pose.orientation.z = 0.0;
markerb2.pose.orientation.w = 1.0;
markerb2.scale.x = 0.4;
markerb2.scale.y = 0.4;
markerb2.scale.z = 0.4;
markerb2.color.a = 1.0;
markerb2.color.r = 0.0;
markerb2.color.g = 0.0;
markerb2.color.b = 0.0;

marker9.ns = "my_namespace9";	 //blue_mm
marker9.id = 0;  
marker9.type = visualization_msgs::Marker::CYLINDER;
marker9.action = visualization_msgs::Marker::ADD;
marker9.pose.position.x = 8.7;
marker9.pose.position.y = -0.8;
marker9.pose.position.z = 0.175;
marker9.pose.orientation.x = 0.7;
marker9.pose.orientation.y = 0.0;
marker9.pose.orientation.z = 0.0;
marker9.pose.orientation.w = 0.7;
marker9.scale.x = 0.35;
marker9.scale.y = 0.15;
marker9.scale.z = 0.15;
marker9.color.a = 1.0;
marker8.color.r = 0.9;
marker9.color.g = 0.5;
marker9.color.b = 0.9;




/*marker4.ns = "my_namespace4";
marker4.id = 0;
marker4.type = visualization_msgs::Marker::SPHERE;
marker4.action = visualization_msgs::Marker::ADD;
marker4.pose.position.x = 5.5;
marker4.pose.position.y = 0.0;
marker4.pose.position.z = 0.1;
marker4.pose.orientation.x = 0.0;
marker4.pose.orientation.y = 0.0;
marker4.pose.orientation.z = 0.0;
marker4.pose.orientation.w = 1.0;
marker4.scale.x = 0.2;
marker4.scale.y = 0.4;
marker4.scale.z = 0.2;
marker4.color.a = 1.0;
marker4.color.r = 0.0;
marker4.color.g = 0.0;
marker4.color.b = 1.0;*/

/*marker5.ns = "my_namespace5"; //plier
marker5.id = 0;
marker5.type = visualization_msgs::Marker::CUBE;
marker5.action = visualization_msgs::Marker::ADD;
marker5.pose.position.x = 3.0;
marker5.pose.position.y = 1.2;
marker5.pose.position.z = 0.05;
marker5.pose.orientation.x = 0.0;
marker5.pose.orientation.y = 0.0;
marker5.pose.orientation.z = 0.0;
marker5.pose.orientation.w = 1.0;
marker5.scale.x = 0.25;
marker5.scale.y = 0.25;
marker5.scale.z = 0.1;
marker5.color.a = 1.0;
marker5.color.r = 0.4;
marker5.color.g = 0.9;
marker5.color.b = 0.2;

marker6.ns = "my_namespace6";		//shampoo_d
marker6.id = 0;
marker6.type = visualization_msgs::Marker::SPHERE;
marker6.action = visualization_msgs::Marker::ADD;
marker6.pose.position.x = 2.5;
marker6.pose.position.y = -1.3;
marker6.pose.position.z = 0.1;
marker6.pose.orientation.x = 0.0;
marker6.pose.orientation.y = 0.0;
marker6.pose.orientation.z = 0.0;
marker6.pose.orientation.w = 1.0;
marker6.scale.x = 0.2;
marker6.scale.y = 0.4;
marker6.scale.z = 0.2;
marker6.color.a = 1.0;
marker6.color.r = 0.0;
marker6.color.g = 0.0;
marker6.color.b = 1.0;



marker8.ns = "my_namespace8";  //mm
marker8.id = 0;
marker8.type = visualization_msgs::Marker::SPHERE;
marker8.action = visualization_msgs::Marker::ADD;
marker8.pose.position.x = 7.7;
marker8.pose.position.y = 2.0;
marker8.pose.position.z = 0.175;
marker8.pose.orientation.x = 0.0;
marker8.pose.orientation.y = 0.0;
marker8.pose.orientation.z = 0.0;
marker8.pose.orientation.w = 1.0;
marker8.scale.x = 0.35;
marker8.scale.y = 0.35;
marker8.scale.z = 0.35;
marker8.color.a = 1.0;
marker8.color.r = 0.2;
marker8.color.g = 0.8;
marker8.color.b = 0.9;


/*marker10.ns = "my_namespace10"; // non-query 
marker10.id = 0;
marker10.type = visualization_msgs::Marker::SPHERE;
marker10.action = visualization_msgs::Marker::ADD;
marker10.pose.position.x = 2.5;
marker10.pose.position.y = -1.0;
marker10.pose.position.z = 0.175;
marker10.pose.orientation.x = 0.0;
marker10.pose.orientation.y = 0.0;
marker10.pose.orientation.z = 0.0;
marker10.pose.orientation.w = 1.0;
marker10.scale.x = 0.3;
marker10.scale.y = 0.3;
marker10.scale.z = 0.3;
marker10.color.a = 1.0;
marker10.color.r = 0.2;
marker10.color.g = 0.8;
marker10.color.b = 0.3;*/

/*
marker10.ns = "my_namespace11";  //toy_car
marker10.id = 0;
marker10.type = visualization_msgs::Marker::CUBE;
marker10.action = visualization_msgs::Marker::ADD;
marker10.pose.position.x = 9.2;
marker10.pose.position.y = 1.0;
marker10.pose.position.z = 0.175;
marker10.pose.orientation.x = 0.0;
marker10.pose.orientation.y = 0.0;
marker10.pose.orientation.z = 0.0;
marker10.pose.orientation.w = 1.0;
marker10.scale.x = 0.25;
marker10.scale.y = 0.25;
marker10.scale.z = 0.25;
marker10.color.a = 1.0;
marker10.color.r = 0.9;
marker10.color.g = 0.1;
marker10.color.b = 0.4; */
}

int main(int argc, char **argv)
{

 ros::init(argc, argv, "p3dx_subscriber");

path.header.frame_id="/map";
/*
marker1.header.frame_id = "/map";
marker1.header.stamp = ros::Time();

marker2.header.frame_id = "/map";
marker2.header.stamp = ros::Time();

marker3.header.frame_id = "/map";
marker3.header.stamp = ros::Time();

marker4.header.frame_id = "/map";
marker4.header.stamp = ros::Time();

marker5.header.frame_id = "/map";
marker5.header.stamp = ros::Time();

marker6.header.frame_id = "/map";
marker6.header.stamp = ros::Time();

marker7.header.frame_id = "/map";
marker7.header.stamp = ros::Time();

marker8.header.frame_id = "/map";
marker8.header.stamp = ros::Time();

marker9.header.frame_id = "/map";
marker9.header.stamp = ros::Time();

marker10.header.frame_id = "/map";
marker10.header.stamp = ros::Time();

marker11.header.frame_id = "/map";
marker11.header.stamp = ros::Time();

marker12.header.frame_id = "/map";
marker12.header.stamp = ros::Time();

marker_o.header.stamp = ros::Time();
marker_o.header.frame_id = "/map";

markerb1.header.stamp = ros::Time();
markerb1.header.frame_id = "/map";

markerq1.header.stamp = ros::Time();
markerq1.header.frame_id = "/map";

markerb2.header.stamp = ros::Time();
markerb2.header.frame_id = "/map";

markerq2.header.stamp = ros::Time();
markerq2.header.frame_id = "/map";*/

ros::NodeHandle n;
//ros::Subscriber pose_sub=n.subscribe<nav_msgs::Odometry>("amcl_pose",10,&pose_callback);
ros::Subscriber pose_sub = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",10,&pose_callback);
ros::Publisher path_pub =  n.advertise<nav_msgs::Path>("Path_5",10);
/*ros::Publisher vis_pub1 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub2 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub3 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub4 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub5 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub6 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub7 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub8 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub9 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub10 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub11 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pubq1 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pubq2 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pubb1 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pubb2 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub_o = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );
ros::Publisher vis_pub12 = n.advertise<visualization_msgs::Marker>( "visualization_marker", 0 );*/

//void pose_callback(const nav_msgs::Odometry::ConstPtr& joy);

void pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& joy);
while(ros::ok())
{
path_pub.publish(path);
/*
vis_pub1.publish( marker1 );
vis_pub2.publish( marker2 );
vis_pub3.publish( marker3 );
vis_pub4.publish( marker4 );
vis_pub5.publish( marker5 );
vis_pub6.publish( marker6 );
vis_pub7.publish( marker7 );
vis_pub8.publish( marker8 );
vis_pub9.publish( marker9 );
vis_pub10.publish( marker10 );
vis_pub11.publish( marker11 );
vis_pub12.publish( marker12 );
vis_pub_o.publish( marker_o );
vis_pubq1.publish( markerq1 );
vis_pubq2.publish( markerq2 );
vis_pubb1.publish( markerb1);
vis_pubb2.publish( markerb2 );*/


ros::Duration(0.1).sleep();
ros::spinOnce();
}



}
//}
