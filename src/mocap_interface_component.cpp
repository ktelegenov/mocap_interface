#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "mocap_interface/mocap_interface_component.hpp"

// using namespace std::chrono_literals;

MocapInterfaceComponent::MocapInterfaceComponent()
: Node("mocap_interface")
{
    // Parameters
    this->declare_parameter("rb_name", "/uav/pose");
    const std::string rigid_body_name = this->get_parameter("rb_name").as_string();
    
    // Subscribers & Publishers
    mocap_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        rigid_body_name, 10, std::bind(&MocapInterfaceComponent::mocap_callback, this, std::placeholders::_1));
    odom_pub_ = this->create_publisher<px4_msgs::msg::VehicleOdometry>(
        "/fmu/in/vehicle_visual_odometry", 10);
        // alternative is /fmu/in/vehicle_mocap_odometry...needs testing

    RCLCPP_INFO(this->get_logger(), "Optitrack Interface to Pixhawk node started.");
}

void MocapInterfaceComponent::mocap_callback(const geometry_msgs::msg::PoseStamped::SharedPtr pose_msg) const 
{
    px4_msgs::msg::VehicleOdometry odom_msg;
	
    odom_msg.pose_frame = odom_msg.POSE_FRAME_FRD;
	odom_msg.timestamp = uint64_t(pose_msg->header.stamp.sec)*1000000 + uint64_t(pose_msg->header.stamp.nanosec)/1000;
	odom_msg.timestamp_sample = odom_msg.timestamp;
	
    odom_msg.position[0] = pose_msg->pose.position.x;
	odom_msg.position[1] = -pose_msg->pose.position.y;
	odom_msg.position[2] = -pose_msg->pose.position.z;

	odom_msg.q[0] = pose_msg->pose.orientation.w;
	odom_msg.q[1] = pose_msg->pose.orientation.x;
	odom_msg.q[2] = - pose_msg->pose.orientation.y;
	odom_msg.q[3] = - pose_msg->pose.orientation.z;
	odom_pub_ -> publish(odom_msg);
}