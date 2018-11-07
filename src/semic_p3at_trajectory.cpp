#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

double trajectory[30];
int t0 = 0, t1 = 0;
std_msgs::String position[30];

bool moviment_status = true;
int moviment_now = 0;
int moviment_size = 4;

void defineTrajectory(){
    trajectory[0] = 5.0;
    trajectory[1] = 30.0;
    trajectory[2] = 180.0;
    trajectory[3] = 8.0;
    trajectory[4] = 180.0;
    trajectory[5] = 90.0;
}

void statusCallback(std_msgs::String status){
    ROS_INFO("Recebi");
    if(status.data == "done")
        moviment_status = true;
}

void turn(ros::Publisher pub, double d, double time){
    std_msgs::Float32 degree;
    degree.data = d;
    pub.publish(degree);
    t0 = ros::Time::now().toSec();
    t1 = t0;
    ROS_INFO("Esperando");
    while(t1 - t0 <= time && ros::ok()){
        t1 = ros::Time::now().toSec();
    }
}

void move(ros::Publisher pub, double d, double time){
    std_msgs::Float32 distance;
    distance.data = d;
    pub.publish(distance);
    t0 = ros::Time::now().toSec();
    t1 = t0;
    ROS_INFO("Esperando");
    while(t1 - t0 <= time && ros::ok()){
        t1 = ros::Time::now().toSec();
    }
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "semic_p3at_trajectory");

    ros::NodeHandle n;
    ros::Publisher pub1 = n.advertise<std_msgs::String>("/semic/p3at/status", 1);
    ros::Publisher pub2 = n.advertise<std_msgs::Float32>("/semic/p3at/move", 1);
    ros::Publisher pub3 = n.advertise<std_msgs::Float32>("/semic/p3at/rotate", 1);
    ros::Subscriber sub = n.subscribe("/semic/p3at/status", 1, &statusCallback);

    std_msgs::String str;
    std_msgs::Float32 distance;
    defineTrajectory();
    ros::Rate loop_rate(1);
    bool p = true;
    std::stringstream ss;
    std_msgs::String msg;
    while(ros::ok()){

            /* Anda até o S1 */
        move(pub2, 0, 0);
        move(pub2, 4, 8);
        turn(pub3, 90, 4);
        move(pub2, 5, 10);
        turn(pub3, 180, 5);
        msg.data = "s1";
        pub1.publish(msg);
        move(pub2, 0, 60);
        /* Anda até o S3 */
        turn(pub3, 180, 5);
        move(pub2, 5, 10);
        turn(pub3, 180, 5);
        msg.data = "s3";
        pub1.publish(msg);
        move(pub2, 0, 60);
        /* Anda até o S2 */
        turn(pub3, 180, 5);
        move(pub2, 3, 6);
        turn(pub3, 180, 5);
        msg.data = "s2";
        pub1.publish(msg);
        move(pub2, 0, 60);
        break;
        ros::spinOnce();
    }
}