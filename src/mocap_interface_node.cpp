#include "mocap_interface/mocap_interface_component.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MocapInterfaceComponent>());
    rclcpp::shutdown();    
    return 0;
}