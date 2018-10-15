#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <sstream>

#define PI 3.1415926535897

double t0 = 0, t1 = 0;

double abs(double data){
    if(data < 0){
        data = data * -1;
    }
    return data;
}

void rotateCallback(const std_msgs::Float32 angle){
    double speedValue = 10;
    double speed = speedValue;
    double relative_angle = 0;
    double angular_speed = 0;
    double current_angle = 0;

    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel", 1);
    ros::Publisher pub2 = n.advertise<std_msgs::String>("/semic/p3at/status", 1);
    geometry_msgs::Twist twist;
    angular_speed = speed*2*PI/360;
    relative_angle = abs(angle.data)*2*PI/360;

    t0 = ros::Time::now().toSec();

    if(angle.data > 0){
        speed = -angular_speed;
    } else if(angle.data < 0){
        speed = angular_speed;
    }

    while(current_angle < relative_angle && ros::ok()){
        twist.angular.x = 0;
        twist.angular.y = 0;
        twist.angular.z = speed;
        pub.publish(twist);
        t1 = ros::Time::now().toSec();
        current_angle = angular_speed*(t1-t0);
    }
    twist.angular.x = 0;
    twist.angular.y = 0;
    twist.angular.z = 0;
    pub.publish(twist);
    std_msgs::String msg;
    std::stringstream ss;
    ss << "done";
    msg.data = ss.str();
    pub2.publish(msg);
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "semic_p3at_rotate");

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/semic/p3at/rotate", 1, &rotateCallback);

    ros::spin();
}