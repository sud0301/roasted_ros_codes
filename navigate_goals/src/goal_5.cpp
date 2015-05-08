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
   
     	goal.target_pose.pose.position.x = 5.0;
      	goal.target_pose.pose.position.y = 0.60;
	goal.target_pose.pose.orientation.z = -0.13;
     	goal.target_pose.pose.orientation.w = 0.99;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//std::cin >> a;

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
     	goal.target_pose.pose.position.x = 5.3;
      	goal.target_pose.pose.position.y = 0.40;
	goal.target_pose.pose.orientation.z = -0.36;
     	goal.target_pose.pose.orientation.w = 0.93;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.4;
      	goal.target_pose.pose.position.y = 1.18;
	goal.target_pose.pose.orientation.z = 0.95;
     	goal.target_pose.pose.orientation.w = 0.32;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
        ac.waitForResult();
	 
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.2;
      	goal.target_pose.pose.position.y = 1.33;
	goal.target_pose.pose.orientation.z = 0.87;
	goal.target_pose.pose.orientation.w = 0.48;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

		goal.target_pose.header.frame_id = "/map";
	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.95;
      	goal.target_pose.pose.position.y = -1.03;
	goal.target_pose.pose.orientation.z = -0.31;
     	goal.target_pose.pose.orientation.w = 0.95;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 6.2;
      	goal.target_pose.pose.position.y = -1.2;
	goal.target_pose.pose.orientation.z = -0.58;
     	goal.target_pose.pose.orientation.w = 0.81;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 7.9;
      	goal.target_pose.pose.position.y = -0.7;
	goal.target_pose.pose.orientation.z = 0.13;
     	goal.target_pose.pose.orientation.w = 0.99;
  	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 8.15;
      	goal.target_pose.pose.position.y = -0.5;
	goal.target_pose.pose.orientation.z = 0.37;
     	goal.target_pose.pose.orientation.w = 0.92;	
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

	//////////////#################333
	/*goal.target_pose.header.frame_id = "/map";
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
