#include <chrono>
#include <string>
#include "rclcpp/rclcpp.hpp"
// Include the header for our custom message. 
// The format is always: <package_name>/msg/<message_name>.hpp
#include "ros2_custom_msgs/msg/robot_status.hpp"

using namespace std::chrono_literals;

class StatusPublisher : public rclcpp::Node
{
public:
  StatusPublisher()
  : Node("status_publisher"), mission_count_(0), battery_level_(100.0)
  {
    // Create publisher for the topic "/robot_status"
    publisher_ = this->create_publisher<ros2_custom_msgs::msg::RobotStatus>("/robot_status", 10);

    // Create a timer that fires every 1000ms (1 second)
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&StatusPublisher::timer_callback, this));
      
    RCLCPP_INFO(this->get_logger(), "Status Publisher Node Started");
  }

private:
  void timer_callback()
  {
    auto message = ros2_custom_msgs::msg::RobotStatus();

    // Populate the message fields as per requirements
    message.robot_name = "Explorer1";
    message.is_active = true;
    message.mission_count = mission_count_;
    message.battery_level = battery_level_;

    // Publish the message
    publisher_->publish(message);

    // Log the output to console
    RCLCPP_INFO(this->get_logger(), 
      "Publishing: robot=%s, battery=%.1f, active=%s, missions=%d", 
      message.robot_name.c_str(), 
      message.battery_level, 
      message.is_active ? "true" : "false",
      message.mission_count);

    // Update variables for next loop
    mission_count_++;
    battery_level_ -= 0.5;
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<ros2_custom_msgs::msg::RobotStatus>::SharedPtr publisher_;
  int32_t mission_count_;
  double battery_level_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StatusPublisher>());
  rclcpp::shutdown();
  return 0;
}
