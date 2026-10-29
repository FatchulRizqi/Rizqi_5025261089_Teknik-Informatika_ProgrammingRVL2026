#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std::chrono_literals;

class CameraNode : public rclcpp::Node {
public:
    CameraNode() : Node("camera_node") {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/camera/image_raw", 10);
       
        cap_.open(0);
        if (!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Gagal membuka kamera!");
            return;
        }

        timer_ = this->create_wall_timer(
            33ms, std::bind(&CameraNode::timer_callback, this));
    }

private:
    void timer_callback() {
        cv::Mat frame;
        cap_ >> frame;
        
        if (!frame.empty()) {
            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
            publisher_->publish(*msg);
        }
    }

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraNode>());
    rclcpp::shutdown();
    return 0;
}
