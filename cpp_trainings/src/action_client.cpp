#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/calc_icc_cord_dif_drive.hpp"
 
class CalcIccCordClient : public rclcpp::Node 
{
public:
    CalcIccCordClient() : Node("add_two_ints_client") 
    {
        threads_.push_back(std::thread(std::bind(&CalcIccCordClient::callAddTwoIntsService, this, 0.0, 0.0, 1.57, 2.0, 2.0,1.0)));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        threads_.push_back(std::thread(std::bind(&CalcIccCordClient::callAddTwoIntsService, this, 4.0 ,5.0, 1.57, 2.5, 3.5, 1.0)));
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        threads_.push_back(std::thread(std::bind(&CalcIccCordClient::callAddTwoIntsService, this, -4.0 ,5.0, 1.57, 2.5, 3.5, 1.0)));
    }

    void callAddTwoIntsService(_Float64 x_, _Float64 y_, _Float64 theta_, _Float64 vel_right_, _Float64 vel_left_, _Float64 distance_)
    {
        auto client = this->create_client<tutorial_interfaces::srv::CalcIccCordDifDrive>("calcIccCord");
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_WARN(this->get_logger()," Waiting for the server to be up...");
        }

        auto request = std::make_shared<tutorial_interfaces::srv::CalcIccCordDifDrive::Request>();
        request->x = x_;
        request->y = y_;
        request->orientation = theta_;
        request->vel_right = vel_right_;
        request->vel_left = vel_left_;
        request->witdh = distance_;
        
        auto future = client->async_send_request(request);
 
        try
        {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(),"x = %f, y = %f ", response->x_icc, response->y_icc);
        }
        catch(const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Service call failed");
        }
        
    }
 
private:
    std::vector<std::thread> threads_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CalcIccCordClient>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}