#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "image_transport/image_transport.h"
#include <ros/ros.h>
#include <boost/foreach.hpp>
#include <sensor_msgs/PointCloud2.h>
#include <time.h>
#include <sensor_msgs/image_encodings.h>	
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>


using namespace std; 
//using namespace
namespace enc=sensor_msgs::image_encodings;

int k=0;
time_t rawtime;

void callback(const sensor_msgs::ImageConstPtr &msg, const sensor_msgs::ImageConstPtr &msg1 )
{
	sensor_msgs::ImageConstPtr msg_depth;
//	sensor_msgs::ImageConstPtr msg_color;
	msg_depth=msg;
//	msg_color=msg1;
	
	stringstream num;
	num<<k;
	time (&rawtime);
  	printf ("The current local time is:%d	 %s",k, ctime (&rawtime));
	
	cv_bridge::CvImagePtr cv_ptr_depth;
//	cv_bridge::CvImagePtr cv_ptr_color;	    	
	try
      	{
    		cv_ptr_depth = cv_bridge::toCvCopy(msg_depth, enc::BGR8);
      	}
    	catch (cv_bridge::Exception& e)
      	{
    		ROS_ERROR("cv_bridge exception: %s", e.what());
    		return;
      	}
//	try
//        {
//                cv_ptr_color = cv_bridge::toCvCopy(msg_color, enc::BGR8);
//        }
//        catch (cv_bridge::Exception& e_1)
//        {
//                ROS_ERROR("cv_bridge exception: %s", e_1.what());
//                return;
//        }


   	cv::Mat filtered_image_depth, filtered_image_color;  
   	cv::cvtColor(cv_ptr_depth->image,filtered_image_depth,CV_BGR2GRAY);
//	cv::cvtColor(cv_ptr_color->image,filtered_image_color,CV_BGR2RGB);

	string path_depth = "/home/sud/Desktop/depth_image/"+num.str()+"_depth.png";
//	string path_color = "/home/sud/Desktop/depth_image/"+num.str()+"_color.png";
//	cout<<filtered_image.rows<<"	"<<filtered_image.cols<<endl;
	
	double minv,maxv;
        cv::minMaxLoc(filtered_image_depth,&minv,&maxv);
        cout << "max: " << maxv << endl;
	
//	cv::Mat image_copy (480,640,CV_16UC1);
//	image_copy= filtered_image;
	imwrite(path_depth,filtered_image_depth);
//	imwrite(path_color,filtered_image_color);
//	cv::Mat depth = cv::imread("depth_image.tiff",CV_LOAD_IMAGE_ANYDEPTH);// | CV_LOAD_IMAGE_ANYCOLOR);
	//assert(depth.type() == CV_16UC1);
	
	/*double min,max;
        cv::minMaxLoc(depth,&min,&max);
        cout << "max: " << max << endl; */

	k++;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "image_raw");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
//	image_transport::ImageTransport it_1(nh);
    	image_transport::Subscriber sub = it.subscribe("camera/depth_registered/image_raw", 1,callback);
//	image_transport::Subscriber sub_1 =it_1.subscribe("camera/rgb/image_raw",1,callback);
//	TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image> sync(sub, sub_1,10);
//	sync.registerCallback(boost::bind(&callback,_1,_2));
	ros::spin();
	return 0;
}
