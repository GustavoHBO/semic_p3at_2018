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

void turn(ros::Publisher pub, std_msgs::Float32 d, double time){
    
}

void move(ros::Publisher pub, std_msgs::Float32 d, double time){
    pub.publish(d);
    t0 = ros::Time::now().toSec();
    t1 = t0;
    while(t1 - t0 <= time && ros::ok()){
        ROS_INFO("Esperando");
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
    std_msgs::Float32 degree;
    defineTrajectory();
    ros::Rate loop_rate(1);
    bool p = true;
    std::stringstream ss;
    std_msgs::String msg;
    while(ros::ok()){

                                                /* Anda até o S1 */
        distance.data = trajectory[0];
        pub2.publish(distance);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        degree.data = trajectory[1];
        pub3.publish(degree);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        distance.data = trajectory[2];
        pub2.publish(distance);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        ss << "s1";
        msg.data = ss.str();
        pub1.publish(msg);

        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }
                                                /* Anda até o S2 */
        distance.data = trajectory[4];
        pub2.publish(distance);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 6 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        degree.data = trajectory[1];
        pub3.publish(degree);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        while(t1 - t0 <= 10 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        ss << "s2";
        msg.data = ss.str();
        pub1.publish(msg);

        while(t1 - t0 <= 5 && ros::ok()){
            t1 = ros::Time::now().toSec();
        }
                                                /* Anda até o LENDA */
        
        degree.data = trajectory[5];
        pub3.publish(degree);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        distance.data = 2.0;
        pub2.publish(distance);
        t0 = ros::Time::now().toSec();
        t1 = t0;
        while(t1 - t0 <= 5 && ros::ok()){
            ROS_INFO("Esperando");
            t1 = ros::Time::now().toSec();
        }

        ss << "s3";
        msg.data = ss.str();
        pub1.publish(msg);

        while(t1 - t0 <= 5 && ros::ok()){
            t1 = ros::Time::now().toSec();
        }

        while(true);

        ros::spinOnce();
    }
}