#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
int a;
    
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    
int main(int argc, char** argv)
{
    	ros::init(argc, argv, "simple_navigation_goals");
    
     	//tell the action client that we want to spin a thread by default
     	MoveBaseClient ac("move_base", true);
   
     	//wait for the action server to come up
     	while(!ac.waitForServer(ros::Duration(5.0)))
	{
       		ROS_INFO("Waiting for the move_base action server to come up");
     	}
   
     	move_base_msgs::MoveBaseGoal goal;
   
     //we'll send a goal to the robot to move 1 meter forward
     	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
   
     	goal.target_pose.pose.position.x = 4.93;
      	goal.target_pose.pose.position.y = -0.76;
	goal.target_pose.pose.orientation.z = 0.38;
     	goal.target_pose.pose.orientation.w = 0.92;
   
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//std::cin >> a;

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
     	goal.target_pose.pose.position.x = 4.93;
      	goal.target_pose.pose.position.y = 0.36;
	goal.target_pose.pose.orientation.z = -0.38;
     	goal.target_pose.pose.orientation.w = 0.92;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.7;
      	goal.target_pose.pose.position.y = 0.57;
	goal.target_pose.pose.orientation.z = -0.8;
     	goal.target_pose.pose.orientation.w = 0.6;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
        ac.waitForResult();
	 
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.12;
      	goal.target_pose.pose.position.y = 1.21;
	goal.target_pose.pose.orientation.z = 0.76;
     	goal.target_pose.pose.orientation.w = 0.64;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.99;
      	goal.target_pose.pose.position.y = -1.22;
	goal.target_pose.pose.orientation.z = -0.6;
     	goal.target_pose.pose.orientation.w = 0.79;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.4;
      	goal.target_pose.pose.position.y = -2.0;
	goal.target_pose.pose.orientation.z = 0;
     	goal.target_pose.pose.orientation.w = 1;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 7.92;
      	goal.target_pose.pose.position.y = -1.0;
	goal.target_pose.pose.orientation.z = 0.13;
     	goal.target_pose.pose.orientation.w = 0.99;
  	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
/*
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 7;
      	goal.target_pose.pose.position.y = 0.4;
	goal.target_pose.pose.orientation.z = 0.3;
     	goal.target_pose.pose.orientation.w = 0.95;	
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 7.58;
      	goal.target_pose.pose.position.y = 2.3;
	goal.target_pose.pose.orientation.z = -0.15;
     	goal.target_pose.pose.orientation.w = 0.99;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

	/*goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.8;
      	goal.target_pose.pose.position.y = 2.39;
	goal.target_pose.pose.orientation.z = 0.105;
     	goal.target_pose.pose.orientation.w = 0.9944;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 8.8;
      	goal.target_pose.pose.position.y = 0.6;
	goal.target_pose.pose.orientation.z = 0.7;
     	goal.target_pose.pose.orientation.w = 0.7;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 3.6;
      	goal.target_pose.pose.position.y = -0.8;
	goal.target_pose.pose.orientation.z = -0.94;
     	goal.target_pose.pose.orientation.w = 0.32;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();*/	
   
     return 0;
   }
