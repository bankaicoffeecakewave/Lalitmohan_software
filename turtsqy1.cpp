#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

ros::Publisher velocityPublisher;
turtlesim::Pose currentPose;

void poseCallback(const turtlesim::Pose::ConstPtr& pose) {
    currentPose = *pose;
}

void rotate(double angular_speed, double relative_angle) {
    geometry_msgs::Twist vel_msg;
    double current_angle = 0.0;
    double t0 = ros::Time::now().toSec();

    vel_msg.linear.x = 0;
    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;
    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;

    vel_msg.angular.z = (angular_speed < 0) ? -fabs(angular_speed) : fabs(angular_speed);

    ros::Rate loop_rate(100);
    do {
        velocityPublisher.publish(vel_msg);
        double t1 = ros::Time::now().toSec();
        current_angle = angular_speed * (t1 - t0);
        ros::spinOnce();
        loop_rate.sleep();
    } while (current_angle < relative_angle);

    vel_msg.angular.z = 0;
    velocityPublisher.publish(vel_msg);
}

void moveFor(double distance, double speed) {
    // Calculate the time needed to move the specified distance at the given speed
    double timeToMove = distance / speed;

    // Create a Twist message to control the turtle's velocity
    geometry_msgs::Twist velMsg;
    velMsg.linear.x = speed;  // Set linear velocity

    // Get the current time
    ros::Time startTime = ros::Time::now();

    // Loop until the specified time has passed
    while (ros::Time::now() - startTime < ros::Duration(timeToMove)) {
        velocityPublisher.publish(velMsg);
        ros::spinOnce();
    }

    // Stop the turtle by publishing zero velocity
    velMsg.linear.x = 0;
    velocityPublisher.publish(velMsg);
}

int main(int argc, char **argv) {
    // Initialize ROS node
    ros::init(argc, argv, "turtle_controller_node");
    ros::NodeHandle nh;

    // Create a publisher to control the turtle's velocity
    velocityPublisher = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    ros::Subscriber poseSubscriber = nh.subscribe("/turtle1/pose", 10, poseCallback);

    // Wait for the turtle pose to be received
    while (ros::ok() && currentPose.x == 0.0 && currentPose.y == 0.0) {
        ros::spinOnce();
    }

    for (int i = 0; i < 4; ++i) {
        // Move the turtle forward for a distance of 2.5 units at a speed of 1.7 unit/s
        moveFor(2.5, 1.7);

        // Rotate the turtle by 90 degrees
        rotate(M_PI/2, M_PI/2);

      
    }

    return 0;
}
