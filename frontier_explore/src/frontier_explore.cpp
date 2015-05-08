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

#define NO_CLUSTERS 8
#define ATTEMPTS 10
#define SIZE 100000

using namespace cv;
using namespace std;

ros::Publisher nextgoal_pub;
ros::Subscriber sub1;

//cv::Mat image(1,1,CV_8U);
float origin_x;
float origin_y;

float x_last;
float y_last;

float get_min ( float dis[], int size);
int a1;
int b1;
int z=0;

cv::Mat occ(b1,a1,CV_8U,cv::Scalar(0));

/*void chatterCallback1 (const nav_msgs::MapMetaData& point  )
{
	ROS_INFO("Received  %lf %lf %lf",point.origin.position.x, point.origin.position.y, point.origin.position.z);
	
	origin_x=point.origin.position.x;
	origin_y=point.origin.position.y;
}
*/
float x_nex=0;
float y_nex=0;

int flag;
void chatterCallback2 (const nav_msgs::OccupancyGrid& point1 )
{
							
	geometry_msgs::PoseStamped next_goal;		
	//cout<<" flag 1 "<<endl;
	
	int a2 = point1.info.width; 
	int b2 = point1.info.height;
	int c= (a2) * (b2);	
	int8_t arr[c];
	
	for(int i=0; i<c; i++)
	{
		arr[i]=point1.data[i];
	} 
	
	int arr2d[b2][a2];
	int count1 =0 ;
	
	for (int i=0; i<b2;i++)
	{		
		for (int j=0;j<a2;j++)
		{
						
			arr2d[i][j]=arr[j+a2*i];
			
			if (arr2d[i][j]==0)
				{arr2d[i][j]=254;}
			
			if (arr2d[i][j]==-1)
				{arr2d[i][j]=205;}
			
			if (arr2d[i][j]==100)
				{arr2d[i][j]=0;}								
					
			if(arr2d[i][j] ==0)
			{				
					//ROS_INFO("Received %d %d %d %d %d %d \t ",a2,b2,i,j,arr2d[i][j],count1);
			count1++;
			}								
		} 
	}
	//cout<<" flag 2 "<<endl;
	cv::Mat occ1(b2,a2,CV_8U,cv::Scalar(0));
					//occ=occ1.reshape(a1,b1);	
	
	for(int i=0; i<b2 ;i++)
	{
		for (int j=0;j<a2;j++)
		{
		occ1.at<uchar>((b2-i-1),(j))=arr2d[i][j];
					//ROS_INFO("%d", occ.at<uchar>(i,j));		
		}				
	}
	//cout<<" flag 3 "<<endl;
	Mat occ(occ1.size(),CV_8U,cv::Scalar(0));
	
	int morph_elem = 0;
	int morph_size = 3;
	int morph_operator = 0;
	int operation=2;
	//const char* window_name = "Morphology Transformations ";

	//namedWindow( window_name, WINDOW_AUTOSIZE );

	Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
	morphologyEx( occ1, occ, operation, element );			//Morphological transformation
 	
	//imshow( window_name, occ );
 	//imwrite("/home/sud/morph4.pgm",);
		

	Mat new_image(occ.size(),CV_8UC3,Scalar(0));
	int no_rows = new_image.rows;
		
	//*******************FRONTIER_SEARCH*****************************	
	int count=0;
	int k=0;
	int l=0;
	int a[SIZE];
	int b[SIZE];
	//cout<< "rows" << new_image.rows<< "columns" << new_image.cols<<endl;
	for(int i=0;i<new_image.rows;i++)
	{
		for( int j=0;j<new_image.cols;j++)
		{
			if (abs((occ.at<uchar>(i,j))-(occ.at<uchar>(i,j+1)))==49)
			{
				a[k]=i;
				b[l]=j;
				k++; l++;
				//int intensity=map.at<uchar>(i,j); 
				//cout<<"value of i and j and intensity value"<<i<<"  "<<j<<"  "<< intensity << std::endl ;
				count++;
				new_image.at<Vec3b>(i,j)[0]=255;
				new_image.at<Vec3b>(i,j)[1]=255;
				new_image.at<Vec3b>(i,j)[2]=255;
       	                        //cout<<endl<< " Count is :" << count<<endl ;
			} 			
		}	
	}	
				//int mid_count=count;
	cout<<" flag 4 "<<endl;	
	for(int j=0;j<new_image.cols;j++)
	{
		for( int i=0;i<new_image.rows;i++)
		{
			if (abs((occ.at<uchar>(i,j))-(occ.at<uchar>(i+1,j)))==49)
			{
				a[k]=i;
				b[l]=j;		
				k++; l++;
							//int intensity =map.at<uchar>(i,j); 
							//cout<<"value of i and j and intensity value"<<i<<"  "<<j<<"  "<< intensity << std::endl ;
				count++;
				new_image.at<Vec3b>(i,j)[0]=255;
				new_image.at<Vec3b>(i,j)[1]=255;
				new_image.at<Vec3b>(i,j)[2]=255;
			} 			
		}	
	}
	//cout<<" flag 5 "<<endl;	
		
	//*************CLUSTERING****************
	
	Mat samples(count,2,CV_32FC3,Scalar(0));
 	for (int i=0 ; i<count ; i++)
	{		
		samples.at<float>(i,0)=a[i];	
	}
	for (int j=0; j<count; j++)
	{
		samples.at<float>(j,1)=b[j];	
	}

	//cout<<" flag 6 "<<endl;
	int clustercount=NO_CLUSTERS;	
	Mat labels;
	int attempts=ATTEMPTS;
	Mat centers;		
	cv::kmeans(samples,clustercount,labels,TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,10000,0.0001),attempts,KMEANS_PP_CENTERS,centers);

	//********************NEXT GOAL******************

	/*for (int i=0;i<count;i++)
	{		
		int c= labels.at<int>(a[i],0);
		int d= centers.at<int>(c,0);
		int e= centers.at<int>(c,1);
		cout<<"labels value " << c <<std::endl;				
	}*/

	ROS_INFO("ORIGIN FROM LL CORNER %lf %lf %lf",point1.info.origin.position.x, point1.info.origin.position.y, point1.info.origin.position.z);

	origin_x=(point1.info.origin.position.x);
	origin_y=(point1.info.origin.position.y);
	//cout<<" flag 7 "<<"origin x "<< origin_x <<"origin y: " << origin_y <<endl;
	
	float origin_y_tl = -origin_x/point1.info.resolution;
	float origin_x_tl = no_rows + origin_y/point1.info.resolution;

	int d[NO_CLUSTERS];
	int e[NO_CLUSTERS];
	float dis[NO_CLUSTERS];
	int y_prev = (-origin_x-x_nex)/point1.info.resolution;
	int x_prev = (no_rows + origin_y/point1.info.resolution)-(y_nex/point1.info.resolution);
	
	for (int j=0; j<NO_CLUSTERS ;j++)
	{	
		 d[j]= centers.at<float>(j,0);
		 e[j]= centers.at<float>(j,1);
		 dis[j]= sqrt((d[j]-x_prev)*(d[j]-x_prev) + (e[j]-y_prev)*(e[j]-y_prev));
		// cout<<"centers value " << d[j]<<" "<< e[j]<<" "<< dis[j]<<std::endl;		
	}
	//cout<<" flag 8 "<<endl;
       	// cout<< "Origin are :" << a[mid_count]*0.05 << "and" << b[mid_count]*0.05 << endl;
	
	for (int i=0 ;i<NO_CLUSTERS;i++)			// 
	{
		d[i]=d[i]-((d[i]-y_prev)/dis[i])*10;
		e[i]=e[i]-((e[i]-x_prev)/dis[i])*10;
	}

	circle(new_image, cvPoint(y_prev,x_prev), 4, CV_RGB(255,255,0), 1,8,0);  		// YELLOW : PREVIOUS POSITION
	
	circle(new_image, cvPoint(origin_y_tl,origin_x_tl), 2, CV_RGB(255,255,0), 1,8,0);
	circle(new_image, cvPoint(origin_y_tl,origin_x_tl), 4, CV_RGB(0,255,255), 1,8,0);
	circle(new_image, cvPoint(origin_y_tl,origin_x_tl), 6, CV_RGB(255,0,255), 1,8,0);

	//ROS_INFO ("MY POSITION FROM TL CORNER x-coor: %d y-coor: %d", y_prev,x_prev);	
	
	for (int k=0; k<NO_CLUSTERS;k++)					//NEW ADDITION TO CODE: STILL TO BE TESTED
	{	
	if( (occ.at<uchar>(d[k],e[k])==205) || (occ.at<uchar>(d[k],e[k])==0) )	
		{
		dis[k]=100000;		
		for (int i=1; i<5; i++)
			for (int j=-i;j<=i;j++)
				for (int r=-i;r<=i;r++)
					{
					new_image.at<Vec3b>(d[k]+j,e[k]+r)[0]=255;
					new_image.at<Vec3b>(d[k]+j,e[k]+r)[1]=255;
					new_image.at<Vec3b>(d[k]+j,e[k]+r)[2]=255;
					}
		}
	}
	
	for(int p=0; p<NO_CLUSTERS;p++)
		for (int i=1; i<5; i++)
			for (int j=-i;j<=i;j++)
				for (int k=-i;k<=i;k++)
				{
				if(occ.at<uchar>(d[p]+j,e[p]+k)!=254)
				{
					for (int i=1; i<5; i++)
						for (int j=-i;j<=i;j++)
							for (int k=-i;k<=i;k++)
								{
								dis[p]=100000;
								new_image.at<Vec3b>(d[p]+j,e[p]+k)[0]=255;
								new_image.at<Vec3b>(d[p]+j,e[p]+k)[1]=255;
								new_image.at<Vec3b>(d[p]+j,e[p]+k)[2]=255;
								}		
				}
				}	
	
	//cout<<" flag 9 "<<endl;	
	int min_i;
	min_i=get_min(dis,NO_CLUSTERS);		
		
	//cout<<" flag 9.1 "<< d[min_i]<<"  "<< e[min_i]<< endl;	
	y_nex= ((x_prev)-(d[min_i]))*point1.info.resolution;//point1.info.resolution;
	//cout<<" flag 9.2 "<<endl;		
	x_nex= ((y_prev)-(e[min_i]))*point1.info.resolution;//point1.info.resolution;
	//cout<<" flag 9.3 "<<endl;		
	
	//float x_next = -x_nex; // REQ FOR ODOM FRAME CALCULATIONS
	//float y_next = y_nex; //
	 
	float x_next=(e[min_i]-origin_y_tl)*point1.info.resolution;   //FOR DIRECT MAP FRAME
	float y_next= (-(d[min_i]-origin_x_tl))*point1.info.resolution;
	
	//cout<<" flag 9 "<<endl;	
	//cout<<"x_next: "<<x_next<<" y_next: "<<y_next<<std::endl;
	//cout<<" flag 10 "<<endl;
	
	int c0=0;								//NEW ADDITION TO CODE : TO BE TESTED
	int c1=0;
	int c2=0;
	int c3=0;
	int c4=0;
	int c5=0;
	int c6=0;
	int c7=0;
	int c8=0;
	int c9=0;
	
	for (int i=0;i<count;i++)		
		{		
			int c= labels.at<int>(i,0);
			//float d= centers.at<int>(1,0);
			//float e= centers.at<int>(1,1);
			//cout<<"labels value " << c <<std::endl;				
			
			if(c==0)
			{
			c0++;		
			new_image.at<Vec3b>(a[i],b[i])[0]=255;
			new_image.at<Vec3b>(a[i],b[i])[1]=255;
			new_image.at<Vec3b>(a[i],b[i])[2]=255;			
				if( (occ.at<uchar>(d[0],e[0])!=205) && (occ.at<uchar>(d[0],e[0])!=0) )	
				{ 
				circle(new_image, cvPoint(e[0],d[0]), 2, CV_RGB(255,255,255), 2,8,0); 
				}			
			}

			if(c==1) //RED
			{
			c1++;	
			new_image.at<Vec3b>(a[i],b[i])[0]=0; 
			new_image.at<Vec3b>(a[i],b[i])[1]=0;
			new_image.at<Vec3b>(a[i],b[i])[2]=255;		
			if ((occ.at<uchar>(d[1],e[1])!=205) && (occ.at<uchar>(d[1],e[1])!=0))
				{ 
				circle(new_image, cvPoint(e[1],d[1]), 2, CV_RGB(255,0,0), 2,8,0); 
				}			
			}
			
			if(c==2) //ORANGE
			{
			c2++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=0;
			new_image.at<Vec3b>(a[i],b[i])[1]=127;
			new_image.at<Vec3b>(a[i],b[i])[2]=255;
			if((occ.at<uchar>(d[2],e[2])!=205) && (occ.at<uchar>(d[2],e[2])!=0))	
				{ 
				circle(new_image, cvPoint(e[2],d[2]), 2, CV_RGB(255,127,0), 2,8,0); 
				}
			}

			if(c==3) //YELLOW
			{
			c3++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=0;
			new_image.at<Vec3b>(a[i],b[i])[1]=255;
			new_image.at<Vec3b>(a[i],b[i])[2]=255;		
			if((occ.at<uchar>(d[3],e[3])!=205) && (occ.at<uchar>(d[3],e[3])!=0))	
				{ 
				circle(new_image, cvPoint(e[3],d[3]), 2, CV_RGB(255,255,0), 2,8,0); 
				}			
			}
	
			if(c==4) //GREEN
			{
			c4++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=0;
			new_image.at<Vec3b>(a[i],b[i])[1]=255;
			new_image.at<Vec3b>(a[i],b[i])[2]=0;			

			if((occ.at<uchar>(d[4],e[4])!=205)&& (occ.at<uchar>(d[4],e[4])!=0))	
				{ 
				circle(new_image, cvPoint(e[4],d[4]), 2, CV_RGB(0,255,0), 2,8,0);  
				}			
			}
			
			if(c==5) //BLUE
			{
			c5++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=255;
			new_image.at<Vec3b>(a[i],b[i])[1]=0;
			new_image.at<Vec3b>(a[i],b[i])[2]=0;
			if((occ.at<uchar>(d[5],e[5])!=205) && (occ.at<uchar>(d[5],e[5])!=0))	
				{ 
				circle(new_image, cvPoint(e[5],d[5]), 2, CV_RGB(0,0,255), 2,8,0); 
				}			
			}

			if(c==6) //INDIGO
			{
			c6++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=130;
			new_image.at<Vec3b>(a[i],b[i])[1]=0;
			new_image.at<Vec3b>(a[i],b[i])[2]=75;
			if((occ.at<uchar>(d[6],e[6])!=205) && (occ.at<uchar>(d[6],e[6])!=0))	
				{ 
				circle(new_image, cvPoint(e[6],d[6]), 2, CV_RGB(75,0,130), 2,8,0); 
				}			
			}

			if(c==7) //VIOLET
			{
			c7++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=255;
			new_image.at<Vec3b>(a[i],b[i])[1]=150;
			new_image.at<Vec3b>(a[i],b[i])[2]=143;
			if((occ.at<uchar>(d[7],e[7])!=205) && (occ.at<uchar>(d[7],e[7])!=0))	
				{ 
				circle(new_image, cvPoint(e[7],d[7]), 2, CV_RGB(143,150,255), 2,8,0); 
				}			
			}
			
			if(c==8)
			{
			c8++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=55;
			new_image.at<Vec3b>(a[i],b[i])[1]=55;
			new_image.at<Vec3b>(a[i],b[i])[2]=200;
			if((occ.at<uchar>(d[8],e[8])!=205) && (occ.at<uchar>(d[8],e[8])!=0))	
				{ 
				circle(new_image, cvPoint(e[8],d[8]), 2, CV_RGB(200,55,55), 2,8,0); 
				}			
			}	
			
			if(c==9)
			{
			c9++;			
			new_image.at<Vec3b>(a[i],b[i])[0]=200;
			new_image.at<Vec3b>(a[i],b[i])[1]=200;
			new_image.at<Vec3b>(a[i],b[i])[2]=200;
			if((occ.at<uchar>(d[9],e[9])!=205) && (occ.at<uchar>(d[9],e[9])!=0))	
				{ 
				circle(new_image, cvPoint(e[9],d[9]), 2, CV_RGB(200,200,200), 2,8,0); 
				}			
			}	
				
		}
	//cout<<" flag 11 "<<endl;

	//cout <<"c0 :"<< c0<<" c1 :"<< c1<<" c2 :"<< c2<<" c3 :"<< c3<<" c4 :"<< c4<<" c5 :"<< c5<<" c6 :"<< c6<<" c7 : "<< c7 <<" c8 :"<< c8<<"c9 :"<< c9 <<endl;	
		
	circle(new_image, cvPoint(e[min_i],d[min_i]), 8, CV_RGB(0,255,0), 1,8,0);		//GREEN : GOAL / NEAREST CLUSTER
		
	//***************************************
	
	//cout<<" flag 12 "<<endl;	
	cv::namedWindow("blank1");
	//cv::imshow("blank1",occ);	
	cv::imwrite("/home/sud/fuerte_workspace/sandbox/frontier_explore/maps/occ.jpg",occ);

	cv::namedWindow("blank2");
	cv::imwrite("/home/sud/fuerte_workspace/sandbox/frontier_explore/maps/occ1.jpg",occ1);
	
//	String filename="/workspace/karthik/RRC/ros_workspace/frontier_explore/maps/result"+z+".jpg";
	char filename[100]="/home/sud/fuerte_workspace/sandbox/frontier_explore/maps/result";
//	filename=filename.c_str();
	char extension[10] = ".jpg";
  //      extension=extension.c_str();	
	//std::strcpy(extension,extension.c_str());
	//std::osstringstream filename;
	//string filename="/workspace/karthik/RRC/ros_workspace/frontier_explore/maps/result"<<num.str()<<".jpg";
	sprintf(filename,"%s%d%s",filename,z,extension);
	//cout<<	
	cv::namedWindow("blank");
	//cv::imshow("blank",new_image);	
		
	cv::imwrite(filename,new_image);
	z++;
	//************** PUBLISHING ****************
	
	//cout<<" flag 13 "<<endl;
	
	if (x_last==x_next)
	{
	next_goal.header.frame_id="/map";
	next_goal.pose.position.x=0.0;
	next_goal.pose.position.y=0.0;
	next_goal.pose.position.z=0.0;
	next_goal.pose.orientation.x=0.0;
	next_goal.pose.orientation.y=0.0;
	next_goal.pose.orientation.z=0.0;
	next_goal.pose.orientation.w=1.0;	
	}
	else
	{
	next_goal.header.frame_id="/map";
	next_goal.pose.position.x=x_next;
	next_goal.pose.position.y=y_next;
	next_goal.pose.position.z=0.0;
	next_goal.pose.orientation.x=0.0;
	next_goal.pose.orientation.y=0.0;
	next_goal.pose.orientation.z=0.0;
	next_goal.pose.orientation.w=1.0;		
	}
	ROS_INFO(" NEXT GOAL x:%lf y:%lf ",next_goal.pose.position.x,next_goal.pose.position.y);
	
	
	nextgoal_pub.publish(next_goal);

	 x_last = x_next;
	 y_last = y_next;
	//cout<<" flag sleep now "<<endl;	
	sleep(30);	
	//cout<<" flag sleep over "<<endl;

	//*************************************************
	
								//flag=1;
								//}
								//break;
								//cv::waitKey(0);
								//ros::spinOnce();	        
								//}
}	

/*void Callback (const move_base_msgs::MoveBaseFeedback& point2 )
{
//point2.base_position.header.frame_id="/map";

float x_val=point2.base_position.pose.position.x;
float y_val=point2.base_position.pose.position.y;

ROS_INFO("********** %d %d************8 ",x_val,y_val )

}*/

int main (int  argc, char** argv)
{	
	ros::init(argc,argv,"new_front_explore");
	ros::NodeHandle n;

	sub1 =n.subscribe ("/map",1,chatterCallback2);
	//sub2 =n.subscribe ("/move_base_msgs/MoveBaseActionFeedback",1,callback)	
  	nextgoal_pub =n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal",1);
	
						//while (ros::ok())
						//{
	cout <<"flag MAIN"<<endl;
						//flag=0;
						//ros::spinOnce();
						//sleep(10);	
	//while(ros::ok())
	//{
	
					//}
	ros::spin();	
	//}	
}

float get_min( float dis[] ,int size  )
{
	int i;
	float min;
        int min_i=0;
	min=dis[0];
	for (i=1; i<size; i++)
	{	
		if (dis[i] < min)
		{
		 	min=dis[i];			
			min_i=i;			
		}	
	} 
	return min_i;
}



