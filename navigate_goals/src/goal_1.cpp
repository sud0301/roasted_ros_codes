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
     	goal.target_pose.pose.position.x = 0.35;
      	goal.target_pose.pose.position.y = 1.77;
	goal.target_pose.pose.orientation.z = 0.63;
     	goal.target_pose.pose.orientation.w = 0.77;
   
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//std::cin >> a;

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 2.35;
      	goal.target_pose.pose.position.y = 0.825;	
	goal.target_pose.pose.orientation.z = 0.26;
     	goal.target_pose.pose.orientation.w = 0.96;
  
     	ROS_INFO("Sending goal_2");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 2.44;
      	goal.target_pose.pose.position.y = -0.55;
	goal.target_pose.pose.orientation.z = -0.68;
     	goal.target_pose.pose.orientation.w = 0.73;
  
     	ROS_INFO("Sending goal_3");
     	ac.sendGoal(goal);
        ac.waitForResult();
	 
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 4.76;
      	goal.target_pose.pose.position.y = -0.28;
	goal.target_pose.pose.orientation.z = 0.06;
     	goal.target_pose.pose.orientation.w = 0.99;
  
     	ROS_INFO("Sending goal_4");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.7;
      	goal.target_pose.pose.position.y = -1.43;
	goal.target_pose.pose.orientation.z = -0.42;
     	goal.target_pose.pose.orientation.w = 0.90;
     	ROS_INFO("Sending goal_5");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 7.98;
      	goal.target_pose.pose.position.y = -0.95;
	goal.target_pose.pose.orientation.z = 0.13;
     	goal.target_pose.pose.orientation.w = 0.99;
     	ROS_INFO("Sending goal_6");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 8.84;
      	goal.target_pose.pose.position.y = 0.35;
	goal.target_pose.pose.orientation.z = 0.48;
     	goal.target_pose.pose.orientation.w = 0.87;
  	ROS_INFO("Sending goal_7");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 8.13;
      	goal.target_pose.pose.position.y = 1.38;
	goal.target_pose.pose.orientation.z = 0.88;
     	goal.target_pose.pose.orientation.w = 0.47;	
     	ROS_INFO("Sending goal_8");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 5.72;
      	goal.target_pose.pose.position.y = 1.9;
	goal.target_pose.pose.orientation.z = 0.99;
     	goal.target_pose.pose.orientation.w = 0.09;
     	ROS_INFO("Sending goal_9");
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
