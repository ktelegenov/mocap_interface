from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from launch_yaml.launch_description_sources import YAMLLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    vrpn_mocap_node = IncludeLaunchDescription(
        YAMLLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("vrpn_mocap"),
                "launch/client.launch.yaml",
            )
        ),
        launch_arguments={
            'server' : '192.168.0.101',
            'port' : '3883',
        }.items()
    )
    

    config = os.path.join(
        get_package_share_directory('mocap_interface'),
        'config',
        'params.yaml'
        )

    mocap_interface_node = Node(
        package='mocap_interface',
        executable='mocap_interface_node',
        name='mocap_interface',
        output='screen',
        parameters=[config]
    )

    return LaunchDescription([
        vrpn_mocap_node,
        mocap_interface_node,
    ])