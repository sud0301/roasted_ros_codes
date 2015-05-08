#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

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
#include <sys/time.h>
#include <sensor_msgs/image_encodings.h>

#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <inttypes.h>

using namespace std;
//using namespace
namespace enc=sensor_msgs::image_encodings;

int k=0;
time_t rawtime;
    
using namespace sensor_msgs;
using namespace message_filters;

/*struct timeval GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}*/
	
long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

void print_current_time_with_ms ()
{
   // long            ms; // Milliseconds
   // time_t          s;  // Seconds
   // struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
	//cout<<s<<"_"<<ms<<endl;

//    printf("Current time:%"PRIdMAX " %03ld milliseconds\n",(intmax_t)s, ms);
} 

void callback(const ImageConstPtr& msg_depth, const ImageConstPtr& msg_color)
{
	stringstream num_s,num_ms, num_ss, num_mss;
//	num_s<<s;
//	num_ms<<ms;
	
        time (&rawtime);
       // printf ("The current local time is: %s", ctime (&rawtime));

        cv_bridge::CvImagePtr cv_ptr_depth;
      	cv_bridge::CvImagePtr cv_ptr_color;             
        try
        {
                cv_ptr_depth = cv_bridge::toCvCopy(msg_depth, enc::MONO16);
        }
        catch (cv_bridge::Exception& e)
        {
                ROS_ERROR("cv_bridge exception: %s", e.what());
                return;
        }
      	try
        {
                cv_ptr_color = cv_bridge::toCvCopy(msg_color, enc::RGB8);
        }
        catch (cv_bridge::Exception& e)
        {
                ROS_ERROR("cv_bridge exception_1111111: %s", e.what());
                return;
	}
	cv::Mat filtered_image_depth, filtered_image_color;
	cv::cvtColor(cv_ptr_depth->image,filtered_image_depth,CV_GRAY2RGB);
      	cv::cvtColor(cv_ptr_color->image,filtered_image_color,CV_RGB2BGR);
	
	print_current_time_with_ms();
       	num_s<<s;
        num_ms<<ms;
	string path_depth = "/home/sud/Desktop/depth_image/"+num_s.str()+"_"+num_ms.str()+"_depth.png";
      	imwrite(path_depth,filtered_image_depth);
	
	print_current_time_with_ms();
	//print_current_time_with_ms();
	
	num_ss<<s;
        num_mss<<ms;

	string path_color = "/home/sud/Desktop/depth_image/"+num_ss.str()+"_"+num_mss.str()+"_color.png";
	imwrite(path_color,filtered_image_color);
	
	double minv,maxv;

        cv::minMaxLoc(filtered_image_depth,&minv,&maxv);
        cout << "max: " << maxv << endl;

//	cv::Mat img_mod(filtered_image_depth.rows, filtered_image_depth.cols, CV_8UC1);
/*	cout <<filtered_image_depth.rows<<"	"<<filtered_image_depth.cols<<endl;
        for (int i=1; i < filtered_image_depth.rows; i++)
        {       for (int j=1; j <filtered_image_depth.cols; j++)
               {
                        int val=filtered_image_depth.at<unsigned short>(i,j);
                //      cout<<val;              
                        int val_img = val*255/maxv;
	      	//	cout<<val_img<<" ";
                        img_mod.at<uchar>(i,j)=val_img;
                }
        }
	string path_depth_mod = "/home/sud/Desktop/depth_image/"+num_s.str()+"_"+num_ms.str()+"_depth_new.png";
	imwrite(path_depth_mod,img_mod);
  */     
	// double minv,maxv;
       // cv::minMaxLoc(filtered_image_depth,&minv,&maxv);
       // cout << "max: " << maxv << endl;

   
  	// cv::Mat depth = cv::imread("depth_image.tiff",CV_LOAD_IMAGE_ANYDEPTH);// | CV_LOAD_IMAGE_ANYCOLOR);
        //assert(depth.type() == CV_16UC1);

       // double min,max;
       // cv::minMaxLoc(depth,&min,&max);
       // cout << "max: " << max << endl; */

        k++;
 }
 
int main(int argc, char** argv)
{
	ros::init(argc, argv, "vision_node");
 
	ros::NodeHandle nh;
  	message_filters::Subscriber<Image> image_sub(nh, "camera/depth_registered/image_raw", 10);
 	message_filters::Subscriber<Image> info_sub(nh, "camera/rgb/image_color", 10);
	
	typedef sync_policies::ApproximateTime<Image, Image> MySyncPolicy;
	Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), image_sub, info_sub )	;  	

	
//	TimeSynchronizer<Image, Image> sync(image_sub, info_sub, 10);
   	sync.registerCallback(boost::bind(&callback, _1, _2));
   	cout<<"info"<<endl;
   	ros::spin();
  
  	return 0;
}
