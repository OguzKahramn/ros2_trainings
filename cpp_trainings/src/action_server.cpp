#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/calc_icc_cord_dif_drive.hpp"
#include <cmath>

class CalcIccCord: public rclcpp::Node 
{
public:
    CalcIccCord() : Node("CalcIccCordServer") 
    {
        service_ = this->create_service<tutorial_interfaces::srv::CalcIccCordDifDrive>("calcIccCord",
        std::bind(&CalcIccCord::calculate,this,std::placeholders::_1,std::placeholders::_2)); //std::placeholders::_3, std::placeholders::_4,
        //std::placeholders::_5, std::placeholders::_6));
    }
 
private:
    void calculate(const tutorial_interfaces::srv::CalcIccCordDifDrive::Request::SharedPtr request, 
        const tutorial_interfaces::srv::CalcIccCordDifDrive::Response::SharedPtr response)
    {
        x_ = request->x;
        y_ = request->y;
        theta_ = request->orientation;
        right_vel_ = request->vel_right;
        left_vel_ = request->vel_left;
        distance_ = request->witdh;
        auto r = (distance_/2)*(right_vel_ + left_vel_)*(right_vel_ - left_vel_);
        RCLCPP_INFO(this->get_logger(),"r: %f",r);
        
        response->x_icc = x_ - r* sin(theta_);
        response->y_icc = y_ + r * cos(theta_);
    }
    rclcpp::Service<tutorial_interfaces::srv::CalcIccCordDifDrive>::SharedPtr service_;
    _Float64 x_, y_, theta_, right_vel_, left_vel_, distance_ ;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CalcIccCord>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}