#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <nlohmann/json.hpp>

using nlohmann::json;

class JsonListener : public rclcpp::Node
{
public:
  JsonListener()
  : Node("json_listener")
  {
    sub_ = this->create_subscription<std_msgs::msg::String>(
      "chatter", 10,
      std::bind(&JsonListener::on_msg, this, std::placeholders::_1));
  }

private:
  void on_msg(const std_msgs::msg::String::SharedPtr msg)
  {
    try {
      json j = json::parse(msg->data);
      std::string text = j.value("msg", "");
      int count = j.value("count", -1);
      std::string source = j.value("source", "unknown");

      RCLCPP_INFO(this->get_logger(), "Received json: msg=%s, count=%d, source=%s",
                  text.c_str(), count, source.c_str());
    } catch (const std::exception &e) {
      RCLCPP_WARN(this->get_logger(), "Failed to parse json: %s", e.what());
    }
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JsonListener>());
  rclcpp::shutdown();
  return 0;
}

