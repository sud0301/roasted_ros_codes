
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
     	goal.target_pose.header.frame_id = "/map";   //frontier
     	goal.target_pose.header.stamp = ros::Time::now();
     	goal.target_pose.pose.position.x = 1.0;
      	goal.target_pose.pose.position.y = 2;
	goal.target_pose.pose.orientation.z = 0.7;
     	goal.target_pose.pose.orientation.w = 0.7;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	//std::cin >> a;

	goal.target_pose.header.frame_id = "/map"; 	//shampoo
     	goal.target_pose.header.stamp = ros::Time::now();
     	goal.target_pose.pose.position.x = 0.5;
      	goal.target_pose.pose.position.y = 5.0;
	goal.target_pose.pose.orientation.z = -0.22;
     	goal.target_pose.pose.orientation.w = 0.97;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.frame_id = "/map";	//shampoo 
     	goal.target_pose.header.stamp = ros::Time::now();
     	goal.target_pose.pose.position.x = 0.8;
      	goal.target_pose.pose.position.y = 5.0;
	goal.target_pose.pose.orientation.z = -0.17;
     	goal.target_pose.pose.orientation.w = 0.98;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.stamp = ros::Time::now(); 	//blue_box
	goal.target_pose.pose.position.x = 1.7;
      	goal.target_pose.pose.position.y = 5.4;
	goal.target_pose.pose.orientation.z = -0.26;
     	goal.target_pose.pose.orientation.w = 0.95;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.frame_id = "/map";		//blue_box
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 2.1;
      	goal.target_pose.pose.position.y = 5.1;
	goal.target_pose.pose.orientation.z = 0;
     	goal.target_pose.pose.orientation.w = 1;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";	//cinthol
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 0.8;
      	goal.target_pose.pose.position.y = 5.2;
	goal.target_pose.pose.orientation.z = -0.82; //-135
     	goal.target_pose.pose.orientation.w = 0.57;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
        ac.waitForResult();	
	 

	//////////////#################333
	goal.target_pose.header.frame_id = "/map";	//cinthol
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 0.5;
      	goal.target_pose.pose.position.y = 4.9;
	goal.target_pose.pose.orientation.z = -0.88;
     	goal.target_pose.pose.orientation.w = 0.46;
  
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 0;
      	goal.target_pose.pose.position.y = 7.2;
	goal.target_pose.pose.orientation.z = 0;
     	goal.target_pose.pose.orientation.w = 1;
  	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 1.2;
      	goal.target_pose.pose.position.y = 0;//-1.6;
	goal.target_pose.pose.orientation.z = -0.92;
     	goal.target_pose.pose.orientation.w = 0.38;	
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 1.2;
      	goal.target_pose.pose.position.y = -2.0;//-1.6;
	goal.target_pose.pose.orientation.z = -0.92;
     	goal.target_pose.pose.orientation.w = 0.38;	
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 1;
      	goal.target_pose.pose.position.y = -4.8;
	goal.target_pose.pose.orientation.z = -0.7;
     	goal.target_pose.pose.orientation.w = 0.7;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 0;
      	goal.target_pose.pose.position.y = -6.4;
	goal.target_pose.pose.orientation.z = -0.819;
     	goal.target_pose.pose.orientation.w = 0.57;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = -0.4;
      	goal.target_pose.pose.position.y = -6.8;
	goal.target_pose.pose.orientation.z =-0.9;
     	goal.target_pose.pose.orientation.w = 0.422;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	//////////////#################333
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 1;
      	goal.target_pose.pose.position.y = -7.6;
	goal.target_pose.pose.orientation.z = -0.13;
     	goal.target_pose.pose.orientation.w = 0.99;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();
	
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 1.4;
      	goal.target_pose.pose.position.y = -7.6;
	goal.target_pose.pose.orientation.z = 0.;
     	goal.target_pose.pose.orientation.w = 1;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();	
   
	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 2;
      	goal.target_pose.pose.position.y = -3.6;
	goal.target_pose.pose.orientation.z = 0.;
     	goal.target_pose.pose.orientation.w = 1;
     	ROS_INFO("Sending goal");
     	ac.sendGoal(goal);
     	ac.waitForResult();

	goal.target_pose.header.frame_id = "/map";
     	goal.target_pose.header.stamp = ros::Time::now();
	goal.target_pose.pose.position.x = 2.4;
      	goal.target_pose.pose.position.y = -3.6;
	goal.target_pose.pose.orientation.z = 0.;
     	goal.target_pose.pose.orientation.w = 1;
     	ROS_INFO("Sending goal");

     	ac.sendGoal(goal);
     	ac.waitForResult();
     return 0;
   }
