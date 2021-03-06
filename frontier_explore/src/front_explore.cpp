#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include <cmath>
#include <stdlib.h>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/Pose.h"
#include "nav_msgs/OccupancyGrid.h"
#include "std_msgs/Bool.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
//using namespace msg;
int state;
int px,py,ox,oy;
int thresh=100;
int flag=0;
double home_theta;
float resolution;

double now_x;
double now_y;
double now_theta;
//ros::init(argc,argv,"testing");
//ros::NodeHandle n;

ros::Publisher start_pub;
ros::Publisher goal_pub;

void moveTo(double x, double y, double theta)
{
ROS_INFO("Move to (%lf, %lf, %lf)", x, y, theta);
cout << "Move" << x <<" "<< y;
geometry_msgs::PoseStamped goal;
goal.header.frame_id="/map";
goal.header.stamp=ros::Time::now();

goal.pose.position.x=x;
goal.pose.position.y=y;
goal.pose.orientation=tf::createQuaternionMsgFromRollPitchYaw(0, 0, theta);

goal_pub.publish(goal);

}
int h,w;

void GoalCallback( const nav_msgs::OccupancyGrid &msg)
{ resolution=msg.info.resolution;
// cout<<"resolution" <<resolution << endl;
  ox=-1*msg.info.origin.position.x;
  oy=-1*msg.info.origin.position.y;
  cout << " ox " <<ox << " oy "<< oy<< endl;
  h=msg.info.height;
  w=msg.info.width;

  cout << " h " <<h << " w "<< w<< endl;

  ox=int (ox/resolution);
  oy=int (oy/resolution);

  cout << " ox1 " <<ox << " oy "<< oy<< endl;

  oy=h-oy;
  
    cout << " ox2 " <<ox << " oy "<< oy<< endl;

  if(flag==0)
  {px=ox;
   py=oy;

  //h=msg.info.height;
  //w=msg.info.width;
  Mat src(h,w,CV_8UC1,Scalar(0,0,0));
 // src = imread( "/tmp/map.pgm", 1 );
 int c=0;
  for(int a=0;a<h;a++){
      for(int b=0;b<w;b++){
          if(msg.data[c]==-1){
              src.at<uchar>(a,b)=120;
          }
          else if(msg.data[c]==0){
              src.at<uchar>(a,b)=255;
          }
          else
              src.at<uchar>(a,b)=0;

          c++;
      }
  }
  imwrite( "/home/sud/Desktop/img.png",src);

  blur( src, src, Size(3,3) );

  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  Canny( src, canny_output, thresh, thresh*2, 3 );
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );


 int clusterCount = 15;
  Mat labels;
//  int attempts = 5;
  Mat centers;
  Mat abc = (Mat)contours;
//  Mat x = ;
//   abc.convertTo(x,CV_32F);

  vector<Point2f> l;

  for(int i = 0; i < contours.size(); i++)
    {
      for(int j = 0; j < contours[i].size(); j++){
       // cout << (float)contours[i][j].x << "x" << (float)contours[i][j].y << " ";
          l.push_back(Point((float)contours[i][j].x,(float)contours[i][j].y));
      }
  }

 // Mat a = Mat(l);
// approxPolyDP(contours,yaya,0,true);

double p=kmeans(Mat(l), clusterCount, labels,TermCriteria(), 3, KMEANS_PP_CENTERS, centers);

int x=0,y=0;

  vector<float>k(contours.size());
  for (int i=0; i<contours.size(); i++)
{ int a=centers.at<int>(i,0);
  int b=centers.at<int>(i,1);
  k[i]=std::sqrt((float) ((a-px)^2+(b-py)^2));
}
 float min=k[0];
 for (int i=0; i<contours.size(); i++)
 {for (int j=0;j<contours.size(); j++)
  {if(min>k[i])
   {min=k[i];
    x=centers.at<int>(i,0);
    y=centers.at<int>(i,1);
   }
  }
 }



ROS_INFO("Get Goal");
//if (state==1)
//{
//state=2;
//x*=resolution;y*=resolution;
//int x=10,y=10;
//recordHomePosition();
const geometry_msgs::Quaternion msg_q=msg.info.origin.orientation;
//home_theta=tf::getYaw(msg_q);
//double ln=resolution*sqrt(x*x+y*y);
double beta=atan2(y-oy,x-ox);
//double x_vector=ln*cos(beta+home_theta);
//double y_vector=ln*sin(beta+home_theta);
double x_inner=(x-ox)*resolution;
double y_inner=(y-oy)*resolution;
//home_theta=beta+home_theta;
moveTo(x_inner, y_inner, beta);
px=x;py=y;
std_msgs::Bool t;
t.data=true;
start_pub.publish(t);

ros::Duration(20).sleep();

flag=1;


//}
  }

else
{ //px=msg.info.origin.position.x;
  //py=msg.info.origin.position.y;

    //h=msg.info.height;
    //w=msg.info.width;
    Mat src(h,w,CV_8UC(1),Scalar::all(0));
   // src = imread( "/tmp/map.pgm", 1 );
   int c=0;
    for(int a=0;a<h;a++){
        for(int b=0;b<w;b++){
            if(uchar(msg.data[c])==-1){
                src.at<int>(a,b)=120;
            }
            else if(uchar(msg.data[c])==0){
                src.at<int>(a,b)=255;
            }
            else
                src.at<int>(a,b)=0;

            c++;
        }
    }

  blur( src, src, Size(3,3) );

  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  Canny( src, canny_output, thresh, thresh*2, 3 );
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );



 int clusterCount = 15;
  Mat labels;
//int attempts = 5;
  Mat centers;
  Mat abc = (Mat)contours;
//Mat x = ;
//abc.convertTo(x,CV_32F);

  vector<Point2f> l;

  for(int i = 0; i < contours.size(); i++)
    {
      for(int j = 0; j < contours[i].size(); j++){
       // cout << (float)contours[i][j].x << "x" << (float)contours[i][j].y << " ";
          l.push_back(Point((float)contours[i][j].x,(float)contours[i][j].y));
      }
  }

 // Mat a = Mat(l);
// approxPolyDP(contours,yaya,0,true);

double p=  kmeans(Mat(l), clusterCount, labels,TermCriteria(), 3, KMEANS_PP_CENTERS, centers);

int x=0,y=0;

  vector<float>k(contours.size());
  for (int i=0; i<contours.size(); i++)
{ int a=centers.at<int>(i,0);
  int b=centers.at<int>(i,1);
  k[i]=std::sqrt((float) ((a-px)^2+(b-py)^2));
}
 float min=k[0];
 for (int i=0; i<contours.size(); i++)
 {for (int j=0;j<contours.size(); j++)
  {if(min>k[i])
   {min=k[i];
    x=centers.at<int>(i,0);
    y=centers.at<int>(i,1);
   }
  }
 }



ROS_INFO("Get Goal");
//if (state==1)
//{
//state=2;
//x*=resolution;y*=resolution;
//int x=0,y=0;
//recordHomePosition();
const geometry_msgs::Quaternion msg_q=msg.info.origin.orientation;
//home_theta=tf::getYaw(msg_q);
//double ln=resolution*sqrt(x*x+y*y);
double beta=atan2(y-oy,x-ox);
//double x_vector=ln*cos(beta+home_theta);
//double y_vector=ln*sin(beta+home_theta);
double x_inner=(x-ox)*resolution;
double y_inner=(y-oy)*resolution;
//home_theta=beta+home_theta;
px=x;py=y;
moveTo(x_inner, y_inner, beta);

std_msgs::Bool t;
t.data=true;
start_pub.publish(t);

//ros::Duration(20).sleep();

//}
}
}




  int main(int argc,char **argv){
  state=1;
  ros::init(argc, argv, "testing");
  ros::NodeHandle n;
  //int temp=0;
  //while(temp!=1){
  ros::Subscriber sub=n.subscribe("map",1000,GoalCallback);
  start_pub=n.advertise<std_msgs::Bool>("start",1000);
  goal_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal",1000);
  //}
  ros::spin();

  return 0;
  }
