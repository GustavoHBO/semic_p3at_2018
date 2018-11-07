#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <sstream>

double distance = 0;
double t0 = 0;
double t1 = 0;

void moveCallback(std_msgs::Float32 dist){
    ROS_INFO("Chegou");
    distance = dist.data;
    t0 = ros::Time::now().toSec();
    t1 = t0;
}

double getAbs(double d){
    if(d < 0){
        d*=-1;
    }
    return d;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "semic_p3at");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel", 1);
    ros::Publisher pub2 = n.advertise<std_msgs::String>("/semic/p3at/status", 1);
    ros::Subscriber sub1 = n.subscribe("/semic/p3at/move", 1, &moveCallback);
    double speed = 0.5;
    bool status = false;
    distance = 0;
    t0 = ros::Time::now().toSec();
    t1 = t0;
    while(ros::ok()){
        geometry_msgs::Twist twist;
        if(getAbs(distance) - (speed*(t1-t0)) >= 0 && distance != 0){
            ROS_INFO("Andando %f", speed*(t1-t0));
            if(distance < 0)
                twist.linear.x = -speed;
            else
                twist.linear.x = speed;
            pub.publish(twist);
            t1 = ros::Time::now().toSec();
            status = true;
        } else if(status){
            status = false;
            pub.publish(twist);
            std_msgs::String msg;
            std::stringstream ss;
            ss << "done";
            msg.data = ss.str();
            //pub2.publish(msg);
        } 
        ros::spinOnce();
    }
    return 0;
};