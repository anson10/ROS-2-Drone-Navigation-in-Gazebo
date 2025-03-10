import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    world_file = os.path.join(get_package_share_directory('my_drone'), 'worlds', 'drone_world.sdf')
    return LaunchDescription([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([os.path.join(
                get_package_share_directory('gazebo_ros'), 'launch', 'gzserver.launch.py'
            )]),
            launch_arguments={'world': world_file}.items(),
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([os.path.join(
                get_package_share_directory('gazebo_ros'), 'launch', 'gzclient.launch.py'
            )])
        ),
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=['-entity', 'my_drone', '-file', os.path.join(
                get_package_share_directory('my_drone'), 'models', 'my_drone', 'model.sdf')],
            output='screen'
        )
    ])
