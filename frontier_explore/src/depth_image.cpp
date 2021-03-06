	#include <ros/ros.h>
   #include <image_transport/image_transport.h>
   #include <opencv2/highgui/highgui.hpp>
   #include <cv_bridge/cv_bridge.h>
   
   void imageCallback(const sensor_msgs::ImageConstPtr& msg)
   {
     try
     {
       cv::imwrite ("view", cv_bridge::toCvShare(msg, "mono8")->image);
     //  cv::WaitKey(30);
     }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
     }
   }
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "image_listener");
     ros::NodeHandle nh;
     cv::namedWindow("view");
     cv::startWindowThread();
     image_transport::ImageTransport it(nh);
     image_transport::Subscriber sub = it.subscribe("camera/depth/image_rect", 1, imageCallback);
     ros::spin();
     cv::destroyWindow("view");
   }
