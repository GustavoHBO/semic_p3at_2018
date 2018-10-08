#include <ros/ros.h>
#include <boost/thread.hpp>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>

double d0 = 0;
double d1 = 0;
double distance = 0;
double t0 = 0;
double t1 = 0;
static boost::mutex mutex;

void odomCallback(nav_msgs::Odometry odom){
    //mutex.lock();
    d1 = odom.pose.pose.position.x;
    ROS_INFO("Odometry: %f", d1);
    ROS_INFO("Odometry Diference: %f", d1-d0);
    //mutex.unlock();
}

void threadOdometry(){
    ros::NodeHandle n;
    ros::Subscriber sub1 = n.subscribe("/RosAria/pose", 1, &odomCallback);
    while(ros::ok()){
        ros::spinOnce();
    }
}

void moveCallback(std_msgs::Float32 dist){
    //mutex.lock();
    double speed = 0.5;
    distance = dist.data;
    ROS_INFO("Distance : %f", distance);
    ROS_INFO("Distance D1 : %f", d1);
    d0 = d1;
    t0 = ros::Time::now().toSec();
    t1 = t0;
    //mutex.unlock();
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel", 1);
    while(ros::ok()){
        geometry_msgs::Twist twist;
        //mutex.lock();
        
        if(d1 - d0 < (distance - (speed*(t1-t0)))){
            twist.linear.x = speed;
            pub.publish(twist);
            t1 = ros::Time::now().toSec();
        } else {
            twist.linear.x = 0;
            ROS_INFO("Parando!");
            pub.publish(twist);
            //mutex.unlock();
            break;
        }
        //mutex.unlock();
    }
}

void threadMove(){
    ros::NodeHandle n;
    ros::Subscriber sub2 = n.subscribe("/semic/p3at_move", 1, &moveCallback);
    while(ros::ok()){
        ros::spinOnce();
    }
}

int main(int argc, char** argv){
    ros::init(argc, argv, "test");
    ros::NodeHandle node;
    boost::thread thread_a(threadOdometry);
    boost::thread thread_b(threadMove);
     
    ros::MultiThreadedSpinner spinner(2); // Use 4 threads
    spinner.spin(); // spin() will not return until the node has been shutdown
    //ros::Subscriber sub2 = node.subscribe("/semic/p3at_move", 10, &topicBCallback);
    //ros::Timer timer = node.createTimer(ros::Duration(0.1),timerCallback);
    //ros::spin();
    return 0;
};