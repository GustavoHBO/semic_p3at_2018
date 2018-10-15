#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>

double trajectory[30];
std_msgs::String position[30];

bool moviment_status = true;
int moviment_now = 0;
int moviment_size = 4;

void defineTrajectory(){
    trajectory[0] = 0.0;
    trajectory[1] = 180.0;
    trajectory[2] = 0.0;
    trajectory[3] = 180.0;
}

void statusCallback(std_msgs::String status){
    ROS_INFO("Recebi");
    if(status.data == "done")
        moviment_status = true;
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
    while(ros::ok()){
        for(int i = 0; i < moviment_size && ros::ok(); i++){
            if(moviment_status){
                if(i % 2 == 0){
                    ROS_INFO("Anda");
                    distance.data = 0.0;
                    pub2.publish(distance);
                    moviment_status = false;
                    loop_rate.sleep();
                } else {
                    ROS_INFO("Roda");
                    degree.data = 10.0;
                    pub3.publish(degree);
                    loop_rate.sleep();
                    moviment_status = false;
                }
            } else {
                i--;
            }
            ros::spinOnce();
        }
        ros::spinOnce();
    }
}