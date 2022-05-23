#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/range_sensor.hpp"
#include <time.h>
 
class RangeSensorSub : public rclcpp::Node 
{
public:
    RangeSensorSub() : Node("range_sensor_sub") 
    {
        RCLCPP_INFO(this->get_logger(), "Range sensor publisher node has been started..");
        subscription_ = this->create_subscription<tutorial_interfaces::msg::RangeSensor>("range_sensor",10, 
            std::bind(&RangeSensorSub::callbackTopic,this, std::placeholders::_1));
    }
 
private:
    void callbackTopic(const tutorial_interfaces::msg::RangeSensor::SharedPtr range_value)
    {
        RCLCPP_INFO(this->get_logger(),"At %d time range sensor value is %d", this->get_clock()->now(), range_value->range);
    }
    rclcpp::Subscription<tutorial_interfaces::msg::RangeSensor>::SharedPtr subscription_ ;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RangeSensorSub>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}