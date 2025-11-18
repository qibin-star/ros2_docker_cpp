#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <nlohmann/json.hpp>

using namespace std::chrono_literals;
using nlohmann::json;

class JsonTalker : public rclcpp::Node
{
public:
  JsonTalker()
  : Node("json_talker"), count_(0)
  {
    pub_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
    timer_ = this->create_wall_timer(1s, std::bind(&JsonTalker::on_timer, this));
  }

private:
  void on_timer()
  {
    json j;
    j["msg"] = "Hello from ROS2 C++";
    j["count"] = count_;
    j["source"] = "docker_cpp";

    std_msgs::msg::String msg;
    msg.data = j.dump();  // 序列化为 string

    pub_->publish(msg);
    RCLCPP_INFO(this->get_logger(), "Published: %s", msg.data.c_str());
    ++count_;
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  int count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JsonTalker>());
  rclcpp::shutdown();
  return 0;
}

