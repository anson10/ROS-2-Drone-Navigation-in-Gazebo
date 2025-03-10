cmake_minimum_required(VERSION 3.8)
project(my_drone)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo_ros2_control REQUIRED)

add_executable(drone_teleop src/drone_teleop.cpp)
ament_target_dependencies(drone_teleop rclcpp geometry_msgs)

install(TARGETS
  drone_teleop
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch worlds models
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
