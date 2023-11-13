from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    mocap_optitrack_node = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([get_package_share_directory('mocap_optitrack'), '/launch/mocap.launch.py'])
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
        mocap_optitrack_node,
        mocap_interface_node,
    ])