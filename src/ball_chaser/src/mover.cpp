#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

int main(int argc, char** argv)
{
    // Initialize the arm_mover node
    ros::init(argc, argv, "mover");

    // Create a handle to the mover node
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // Set loop frequency of 10Hz
    ros::Rate loop_rate(10);

    int start_time, elapsed;

    // Get ROS start time
    while (not start_time) {
        start_time = ros::Time::now().toSec();
    }

    while (ros::ok()) {
        // Get ROS elapsed time
        elapsed = ros::Time::now().toSec() - start_time;

        // Set wheel velocities, forward [0.5, 0.0]
        geometry_msgs::Twist motor_command;
        motor_command.linear.x = 0.5;
        motor_command.angular.z = 0.0;

        // Publish angles to drive the robot
        motor_command_publisher.publish(motor_command);
        

        // Sleep for the time remaining until 10 Hz is reached
        loop_rate.sleep();
    }

    return 0;
}
