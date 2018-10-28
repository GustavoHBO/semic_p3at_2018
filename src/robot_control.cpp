#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    tf::TransformBroadcaster broadcaster;
    ros::Rate loop_rate(30);

    const double degree = M_PI/180;

    double position_wheel1 = 0.0, position_wheel2 = 0.0, position_wheel3 = 0.0, position_wheel4 = 0.0;
    double inc_position_wheel1 = 0.0, inc_position_wheel2 = 0.0, inc_position_wheel3 = 0.0, inc_position_wheel4 = 0.0;
    double angle = 0.0;
    double step = 0.005;
    geometry_msgs::TransformStamped odom_trans;
    sensor_msgs::JointState joint_state;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    while(ros::ok()){
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(4);
        joint_state.name[0] = "p3at_front_left_wheel_joint";
        joint_state.position[0] = position_wheel1;
        joint_state.name[1] = "p3at_front_right_wheel_joint";
        joint_state.position[1] = position_wheel2;
        joint_state.name[2] = "p3at_back_left_wheel_joint";
        joint_state.position[2] = position_wheel3;
        joint_state.name[4] = "p3at_back_right_wheel_joint";
        joint_state.position[4] = position_wheel4;

        odom_trans.header.stamp = ros::Time::now();
        odom_trans.transform.translation.x = cos(angle);
        odom_trans.transform.translation.y = sin(angle);
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(angle);

        joint_pub.publish(joint_state);
        broadcaster.sendTransform(odom_trans);
        if(position_wheel1 < -3.14 || position_wheel1 > 3.14) inc_position_wheel1 *= -1;
        position_wheel1 += inc_position_wheel1;
        if(position_wheel2 < -3.14 || position_wheel2 > 3.14) inc_position_wheel2 *= -1;
        position_wheel2 += inc_position_wheel2;
        if(position_wheel3 < -3.14 || position_wheel3 > 3.14) inc_position_wheel3 *= -1;
        position_wheel3 += inc_position_wheel3;
        if(position_wheel4 < -3.14 || position_wheel4 > 3.14) inc_position_wheel4 *= -1;
        position_wheel4 += inc_position_wheel4;

        loop_rate.sleep();
    }

    return 0;
}
