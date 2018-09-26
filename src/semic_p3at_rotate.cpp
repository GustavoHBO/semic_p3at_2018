#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sstream>

#define RAD 0.0174533

int main(int argc, char **argv){
    ros::init(argc, argv, "semic_p3at");
    ros::NodeHandle n;
    //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("message", 1000);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
    ros::Rate loop_rate(10);
    while (ros::ok()){
        geometry_msgs::Twist twist;
        //std_msgs::String msg;
        //std::stringstream ss;
        //ss << " I am the example1_a node ";
        //msg.data = ss.str();
        twist.angular.z = 10;
        //ROS_INFO("%s", msg.data.c_str());
        pub.publish(twist);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}