#ifndef MOCAP_INTERFACE__MOCAP_INTERFACE_COMPONENT_HPP_
#define MOCAP_INTERFACE__MOCAP_INTERFACE_COMPONENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "std_msgs/msg/string.hpp"
#include "px4_msgs/msg/vehicle_odometry.hpp"

class MocapInterfaceComponent : public rclcpp::Node
{
public:
    MocapInterfaceComponent();

private:
    void mocap_callback(const geometry_msgs::msg::PoseStamped::SharedPtr pose_msg) const;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr mocap_sub_;
    rclcpp::Publisher<px4_msgs::msg::VehicleOdometry>::SharedPtr odom_pub_;
};

#endif