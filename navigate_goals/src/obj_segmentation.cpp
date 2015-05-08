#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <boost/foreach.hpp>
#include <sensor_msgs/PointCloud2.h>

#include <pcl/common/common.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/console/print.h>

#include <flann/flann.h>
#include <flann/io/hdf5.h>
#include <boost/filesystem.hpp>

#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/vfh.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/surface/convex_hull.h>
#include <pcl/segmentation/extract_polygonal_prism_data.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/statistical_outlier_removal.h>

using namespace std;

typedef pcl::PointXYZRGB Point;
typedef pcl::PointCloud<pcl::PointXYZRGB> cloudxyz;
typedef cloudxyz::Ptr cloudptr;
typedef pcl::search::KdTree<Point>::Ptr KdTreePtr;

typedef std::pair<std::string, std::vector<float> > vfh_model;

ros::Publisher pub1;
ros::Publisher pub2;
ros::Publisher pub3;
ros::Publisher pub4;

cloudxyz PC;
string object_ID;
int k=0;

void writeCloudPCD(cloudptr &cloud, string S)
{
	//	cout<<"Writing the cloud "<<S;
	pcl::io::savePCDFileBinary(S, *cloud);
	//	cout<<" Done"<<endl;
}
void displayContents(cloudptr &cloud, string S)
{
	//	cout<<"Size of the "<<S<<" is "<<cloud->size()<<endl;
	//	cout<<"Height of the cloud is "<<cloud->height<<endl;
	//	cout<<"Width of the cloud is "<<cloud->width<<endl;
}
void callback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
	//	cout<<"In the callback ..."<<endl;
	cloudptr cloud_in (new cloudxyz());
	pcl::fromROSMsg(*msg, *cloud_in);
	
	//cloudptr cloud_out (new cloudxyz());
	cloudptr cloud (new cloudxyz());

	pcl::PassThrough<Point> pass_;
	pass_.setFilterFieldName("z");
	pass_.setFilterLimits(0.0, 3.0);
	pass_.setInputCloud(cloud_in);
	pass_.filter(*cloud);

	//Publish filtered points

	sensor_msgs::PointCloud2 passfilter;
	pcl::toROSMsg(*cloud, passfilter);
	passfilter.header.frame_id = msg->header.frame_id;
	pub2.publish(passfilter);

	if(cloud->points.size()<300)
	{
		cout<<"Filtered cloud's size is less than the threshold"<<endl;
		return;

	}


	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZRGB>);


	// Create the filtering object: downsample the dataset using a leaf size of 1cm
	//pcl::VoxelGrid<pcl::PointXYZ> vg;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGB>);
	/*vg.setInputCloud (cloud);
	vg.setLeafSize (0.01, 0.01, 0.01);
	vg.filter (*cloud_filtered);*/
	cloud_filtered=cloud;	
	
	// Create the segmentation object for the planar model and set all the parameters
	pcl::SACSegmentation<pcl::PointXYZRGB> seg;
	pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
	pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZRGB> ());
	pcl::PCDWriter writer;
	seg.setOptimizeCoefficients (true);
	seg.setModelType (pcl::SACMODEL_PLANE);
	seg.setMethodType (pcl::SAC_RANSAC);
	seg.setMaxIterations (100);
	seg.setDistanceThreshold (0.02);

	int i=0, nr_points = (int) cloud_filtered->points.size ();
	while (cloud_filtered->points.size () > 0.3 * nr_points)
	{
		// Segment the largest planar component from the remaining cloud
		seg.setInputCloud (cloud_filtered);
		seg.segment (*inliers, *coefficients);
		if (inliers->indices.size () == 0)
		{
			std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
			break;
		}

		// Extract the planar inliers from the input cloud
		pcl::ExtractIndices<pcl::PointXYZRGB> extract;
		extract.setInputCloud (cloud_filtered);
		extract.setIndices (inliers);
		extract.setNegative (false);

		// Write the planar inliers to disk
		extract.filter (*cloud_plane);
		//		std::cout << "PointCloud representing the planar component: " << cloud_plane->points.size () << " data points." << std::endl;

		// Remove the planar inliers, extract the rest
		extract.setNegative (true);
		extract.filter (*cloud_f);
		cloud_filtered = cloud_f;
	}

	//Remove the outliers
	cloudptr object (new cloudxyz());
	pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
	sor.setInputCloud (cloud_filtered);
	sor.setMeanK(50);
	sor.setStddevMulThresh (1.0);
	sor.filter(*object);

	
	
	/*
	// Creating the KdTree object for the search method of the extraction
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud (cloud_filtered);

	std::vector<pcl::PointIndices> cluster_indices;
	pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
	ec.setClusterTolerance (0.02); // 2cm
	ec.setMinClusterSize (100);
	ec.setMaxClusterSize (25000);
	ec.setSearchMethod (tree);
	ec.setInputCloud (cloud_filtered);
	ec.extract (cluster_indices);

	int j = 0;
	for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
	{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);
	for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
	cloud_cluster->points.push_back (cloud_filtered->points[*pit]); //
	cloud_cluster->width = cloud_cluster->points.size ();
	cloud_cluster->height = 1;
	cloud_cluster->is_dense = true;

	//		std::cout << "PointCloud representing the Cluster: " << cloud_cluster->points.size () << " data points." << std::endl;
	sensor_msgs::PointCloud2 objects;
	pcl::toROSMsg(*cloud_cluster, objects);
	objects.header.frame_id = msg->header.frame_id;
	pub1.publish(objects);

	//	int k;
	//	cout<<"Enter num"<<endl;
	//	cin>>k;
	*/
	//vfh estimation of the each object cluster

	pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());
	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr normals_tree_ (new pcl::search::KdTree<pcl::PointXYZRGB> ());
	pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> normal_;
	normal_.setKSearch(10);
	normal_.setSearchMethod(normals_tree_);
	normal_.setInputCloud(object);
	normal_.compute(*normals);
	//		cout<<"Normals for vfh is computed"<<endl;
	pcl::VFHEstimation<pcl::PointXYZRGB, pcl::Normal, pcl::VFHSignature308> vfh;
	vfh.setInputCloud(object);
	vfh.setInputNormals(normals);

	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree_ (new pcl::search::KdTree<pcl::PointXYZRGB> ());
	vfh.setSearchMethod(tree_);

	pcl::PointCloud<pcl::VFHSignature308>::Ptr vfhs(new pcl::PointCloud<pcl::VFHSignature308> ());

	vfh.compute (*vfhs);
	cout<<"The vfh signature are computed"<<endl;

	//Writing the object cloud
	stringstream num;
	num<<k;
	string path = "/home/sud/fuerte_workspace/sandbox/navigate_goal/bottle/"+object_ID+"/"+object_ID+"_orientation"+num.str()+".pcd";
	writeCloudPCD(object, path);
	string path2 = "/home/sud/fuerte_workspace/sandbox/navigate_goal/bottle/"+object_ID+"/"+object_ID+"_orientation_"+num.str()+".pcd";
	writeCloudPCD(cloud_in, path2);
	cout<<"Done writng the object cloud"<<endl;
	
	//Writing the vfh signature of the cloud
	string path1 = "/home/sud/fuerte_workspace/sandbox/navigate_goal/bottle/"+object_ID+"/"+object_ID+"_orientation"+num.str()+"_vfh.pcd";
	pcl::io::savePCDFileASCII(path1, *vfhs);
	
	//cloud_out =*vfhs;	
	cout<<"Done creating the vfh feature for object "<<endl;
	
	cout<<object->width <<" " << object->height<<" "<< object->points.size() <<endl;
	
	 for (size_t i = 0; i < object->points.size (); ++i)
	{   	 
		cout << "  " << object->points[i].x<<"\t";
              	cout<< " " << object->points[i].y<<"\t";
             	cout<< " "<< object->points[i].z<<endl; ;	
	}	
	//cout<<object->x<<endl;	
	k++;
	//int a;
	//cout<<"Press enter when your pose "<<k<<" is ready"<<endl;
	//cin>>a;
	
	sleep(5);
	cout<<"sleeping";
}	



int main(int argc, char **argv)
{
	ros::init(argc, argv, "obj_segment");
	if(argc<2)
	{
		cout<<"Enter the ID of the object"<<endl;
		exit(0);

	}

	object_ID =argv[1];
	
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe("camera/depth_registered/points", 1, callback);
	pub1 = nh.advertise<sensor_msgs::PointCloud2> ("/camera/depth/objects", 1);
	pub2 = nh.advertise<sensor_msgs::PointCloud2> ("/camera/depth/passthrough", 1);
	
	ros::spin();
}
