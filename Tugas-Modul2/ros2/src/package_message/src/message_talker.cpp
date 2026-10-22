#include "rclcpp/rclcpp.hpp"
#include "custom_message/msg/controller.hpp"
#include <chrono>

using namespace std::chrono_literals;

class ControllerPublisher : public rclcpp::Node {
public:
  ControllerPublisher() : Node("controller_publisher") {
    pub_pos = this->create_publisher<custom_message::msg::Controller>("controller", 10);
    timer_ = this->create_wall_timer(1000ms, std::bind(&ControllerPublisher::timer_callback, this));
  }
private:
  void timer_callback() {
    auto msg = custom_message::msg::Controller();
    // Simulasi data pergerakan robot
    msg.velx = 1.5;   // Maju kecepatan 1.5
    msg.vely = 0.0;   // Tidak bergeser ke samping
    msg.angvel = 0.5; // Berputar perlahan

    RCLCPP_INFO(this->get_logger(), "Mengirim Data: X=%.2f, Y=%.2f, Rotasi=%.2f", msg.velx, msg.vely, msg.angvel);
    pub_pos->publish(msg);
  }
  rclcpp::Publisher<custom_message::msg::Controller>::SharedPtr pub_pos;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControllerPublisher>());
  rclcpp::shutdown();
  return 0;
}
