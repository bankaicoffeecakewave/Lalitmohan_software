#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>

ros::Publisher velocityPublisher;
turtlesim::Pose currentPose;

void poseCallback(const turtlesim::Pose::ConstPtr& poseMsg) {
    currentPose = *poseMsg;
}

void moveTurtleInCircle(double radius) {
    geometry_msgs::Twist velMsg;
    ros::Rate loopRate(10);  // Adjust the loop rate as needed

    double angle = 0.0;
    double angularSpeed = 0.5;  // Adjust angular speed as needed

    while (ros::ok() && angle < 2 * M_PI) {
        velMsg.linear.x = radius * angularSpeed;
        velMsg.angular.z = angularSpeed;

        velocityPublisher.publish(velMsg);

        ros::spinOnce();
        loopRate.sleep();

        angle += angularSpeed / 10.0;  // Incremental update based on loop rate
    }

    velMsg.linear.x = 0.0;
    velMsg.angular.z = 0.0;
    velocityPublisher.publish(velMsg);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "circle_turtle");
    ros::NodeHandle nodeHandle;

    velocityPublisher = nodeHandle.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
    ros::Subscriber poseSubscriber = nodeHandle.subscribe("/turtle1/pose", 1, poseCallback);

    double radius;
    std::cout << "Enter the radius of the circle: ";
    std::cin >> radius;

    moveTurtleInCircle(radius);

    return 0;
}
