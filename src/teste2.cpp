#include "ros/ros.h"
#include "semic_p3at_2018/Service_Odometry.h"
#include <cstdlib>

int main(int argc, char **argv){

	ros::init(argc, argv, "service_example_client");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<semic_p3at_2018::Service_Odometry>("example_serv");
	
	semic_p3at_2018::Service_Odometry srv;
	srv.request.odometry = 20;
	if(client.call(srv)){
		ROS_INFO("Response is : %d", srv.response.h);
	}
	ROS_INFO("Ready");
	ros::spin();
	return 0;
}
