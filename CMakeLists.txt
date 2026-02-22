cmake_minimum_required(VERSION 3.8)
project(ros2_custom_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Find Dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 2. Generate the Custom Message
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotStatus.msg"
)

# 3. Create the Publisher Executable
add_executable(status_publisher src/status_publisher.cpp)
ament_target_dependencies(status_publisher rclcpp)

# 4. Link the Custom Message to the Executable
# This ensures the C++ node can "see" the generated message headers
rosidl_target_interfaces(status_publisher
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# 5. Install Rules
install(TARGETS status_publisher
  DESTINATION lib/${PROJECT_NAME})

ament_package()
