#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
ros::Publisher velocity_publisher;
turtlesim::Pose turtlesim_pose;

void moveinCircle(double linear_velocity, double radius) {
geometry_msgs::Twist vel_msg;
vel_msg.linear.x = linear_velocity;
vel_msg.angular.z = linear_velocity / radius;

 velocity_publisher.publish(vel_msg);
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "circle_turtle_node");
    ros::NodeHandle nh;

    velocity_publisher = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    
    double linear_velocity, radius;

    // Get user input for linear velocity
    std::cout << "Enter linear velocity: ";
    std::cin >> linear_velocity;

    // Get user input for radius
    std::cout << "Enter radius: ";
    std::cin >> radius;

    
    ros::Rate loop_rate(1); 
    while (ros::ok()) {
        moveinCircle(linear_velocity, radius);
        ros::spinOnce();
        loop_rate.sleep();
    }
return 0 ;

}

