#include "rclcpp/rclcpp.hpp"
#include "custom_message/msg/controller.hpp"
#include <cstring> // Diperlukan untuk fungsi memcpy

class ControllerSubscriber : public rclcpp::Node {
public:
  ControllerSubscriber() : Node("controller_subscriber") {
    sub_controller = this->create_subscription<custom_message::msg::Controller>(
      "controller", 10, std::bind(&ControllerSubscriber::controllerCallback, this, std::placeholders::_1)
    );
  }
private:
  // Perhatikan penggunaan tipe pointer 'SharedPtr' di sini
  void controllerCallback(const custom_message::msg::Controller::SharedPtr msg) {
    uint8_t arr[20] = {0}; // Inisialisasi array kosong
    
    // Memasukkan 4 byte float ke dalam array byte
    memcpy(arr + 3, &msg->velx, 4);
    memcpy(arr + 7, &msg->vely, 4);
    memcpy(arr + 11, &msg->angvel, 4);

    RCLCPP_INFO(this->get_logger(), "Data diterima dan di-parsing ke array memory. VelX: %.2f", msg->velx);
  }
  rclcpp::Subscription<custom_message::msg::Controller>::SharedPtr sub_controller;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControllerSubscriber>());
  rclcpp::shutdown();
  return 0;
}
