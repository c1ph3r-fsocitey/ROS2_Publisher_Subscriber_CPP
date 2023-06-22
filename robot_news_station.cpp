#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
class RobotNewsStation : public rclcpp::Node // MODIFY NAME
{
public:
    RobotNewsStation() : Node("robot_news_station"), robot_name("c1ph3r") // MODIFY NAME
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&RobotNewsStation::PublishNews, this));
        RCLCPP_INFO(get_logger(), "This node has been started");
        
    }

private:
    void PublishNews()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("hi this is ") + robot_name;
        publisher_->publish(msg);
    }
    std::string robot_name;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStation>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}