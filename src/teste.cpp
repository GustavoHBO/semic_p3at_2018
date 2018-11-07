#include "ros/ros.h"
#include "semic_p3at_2018/Service_Odometry.h"

bool add(semic_p3at_2018::Service_Odometry::Request &req, semic_p3at_2018::Service_Odometry::Response &res){
 	res.h = 10;
	ROS_INFO("%d", req.odometry);
	return true;
}

int main(int argc, char **argv){

	ros::init(argc, argv, "service_example");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("example_serv", add);
	ROS_INFO("Ready");
	ros::spin();
	return 0;
}
