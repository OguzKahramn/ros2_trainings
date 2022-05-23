#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/range_sensor.hpp"
 
class RangeSensorPub : public rclcpp::Node 
{
public:
    RangeSensorPub() : Node("range_sensor_pub") 
    {
        RCLCPP_INFO(this->get_logger(),"Range Sensor publisher node has been started..");
        publisher_ = this->create_publisher<tutorial_interfaces::msg::RangeSensor>("range_sensor",10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
            std::bind(&RangeSensorPub::callbackSensor,this));
    }
 
private:
    void callbackSensor()
    {   
        auto range_value = tutorial_interfaces::msg::RangeSensor();
        int value = std::rand() % 100 + 1;
        range_value.range = value;
        RCLCPP_INFO(this->get_logger(), "A range value is publishing .. ");
        publisher_->publish(range_value);

    }
    rclcpp::Publisher<tutorial_interfaces::msg::RangeSensor>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RangeSensorPub>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}