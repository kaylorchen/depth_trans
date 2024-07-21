#include "rclcpp/rclcpp.hpp"
#include "iostream"
#include "sensor_msgs/msg/image.hpp"

 class DepthTransform: public rclcpp::Node{
  public:
  DepthTransform():Node("Node"){
    RCLCPP_INFO(this->get_logger(), "DepthTransform ...");
    int count = 10;
    for (int i = 0; i < count; ++i) {
      publishers_.push_back(this->create_publisher<sensor_msgs::msg::Image>("depth_transform" + std::to_string(i), 10));
    }
    auto function = [=](sensor_msgs::msg::Image::SharedPtr msg ){
      RCLCPP_INFO(this->get_logger(),"count = %d", count);
      for (int i = 0; i < count; ++i) {
        RCLCPP_INFO(this->get_logger(), "DepthTransform callback %d", i);
        msg->header.frame_id = "depth_transform" + std::to_string(i);
        publishers_.at(i)->publish(*msg);
      }
    };
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>("/camera/depth/image_raw", 10, function);
  }
  private:
  std::vector<rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr> publishers_;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char **argv){
  std::cout << "depth transformation" << std::endl;
  rclcpp::init(argc, argv);
  auto node = std::make_shared<DepthTransform>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}