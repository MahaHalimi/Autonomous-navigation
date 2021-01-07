#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include "geometry_msgs/Twist.h"
#include <stdio.h>

float right, left,front,fleft,fright;

sensor_msgs::LaserScan LS_value;
geometry_msgs::Twist act;

void LS_Callback(const sensor_msgs::LaserScan::ConstPtr &msg) 
{

	int ranges = msg->ranges.size();
	LS_value.header.stamp = msg->header.stamp;
	LS_value.header.frame_id = msg->header.frame_id;
	LS_value.angle_min = msg->angle_min;
	LS_value.angle_max = msg->angle_max;
	LS_value.angle_increment = msg->angle_increment;
	LS_value.time_increment = msg->time_increment;
	LS_value.range_min = 0.0;
	LS_value.range_max = 100.0;	
	LS_value.ranges.resize(ranges);


	for (int i=0; i <ranges; i++ )

	{
		LS_value.ranges[i] = msg->ranges[i]+1;

		right = LS_value.ranges[i > 0 && i < 143];
		fright = LS_value.ranges[i > 144 && i < 287] ;
		front = LS_value.ranges[i > 288 && i < 431] ;
		fleft = LS_value.ranges[i > 432 && i < 575]  ;
		left = LS_value.ranges[i > 576 && i < 719] ;

		ROS_INFO("Data_LS 'right': %f", right );
		 
/*
		if ( front > 1 && fleft > 1 && fright > 1)
		{
		   ROS_INFO("Data_LS 'right': %f", right );
		   ROS_INFO("Data_LS 'front': %f", front );
		   act.linear.x = 1.0;
		   act.angular.z = 0.0;
		}
		else 
		{
			act.linear.x = 0.0;
			act.angular.z = 0.8;
		}
*/

	}

	
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "reading_laser");
	ros::NodeHandle n;

	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);
	ros::Rate loop_rate(10);

	ros::Subscriber sub = n.subscribe("/m2wr/laser/scan", 100, LS_Callback);

    while(ros::ok())
    {
        
		chatter_pub.publish(act);		
		ros::spinOnce();
		
    }
    return 0;

}

