#include <ros/ros.h>
#include "std_msgs/String.h"
#include <sensor_msgs/LaserScan.h>
#include <stdio.h>

ros::Subscriber sub;
ros::Publisher pub ;
sensor_msgs::LaserScan LS_value;

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

		ROS_INFO("Data_LS: %f", LS_value.ranges[i] );

 }
	
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "reading_laser");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("/m2wr/laser/scan", 100, LS_Callback);

    while(ros::ok())
    {
		
		ros::spinOnce();
		//loop.sleep();
    }
    return 0;

}

