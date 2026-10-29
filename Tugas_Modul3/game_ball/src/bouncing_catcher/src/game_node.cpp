#include <cstdlib>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/int32.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <random>

struct bola {
  double x, y;
  double kecepatan_x, kecepatan_y;
  double sentuh_bola;
  bool disentuh = false;
};

class GameNode : public rclcpp::Node {
  public:
    GameNode() : Node("Game_Node"), score_(0) {
      // parameter yang dibutuhkan
      this->declare_parameter("num_balls", 3);
      this->declare_parameter("hold_duration", 2.0);
      this->declare_parameter("ball_radius", 50);
      this->declare_parameter("ball_speed", 150.0);
      this->declare_parameter("min_area", 300);

      this->declare_parameter("hsv_lower", std::vector<int64_t>{40, 40, 40});
      this->declare_parameter("hsv_upper", std::vector<int64_t>{85, 255, 255});

      score_pub_ = this->create_publisher<std_msgs::msg::Int32>("/game/score", 10);
      image_pub_ = this->create_publisher<sensor_msgs::msg::Image>("/game/debug_image", 10);

      image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
          "/camera/image_raw", 10,
          std::bind(&GameNode::callback_gambar, this, std::placeholders::_1)
      );
      
      game_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(33), 
        std::bind(&GameNode::update_game, this)
      );

      waktu_ = this->now().seconds();

      int jumlah_bola = this->get_parameter("num_balls").as_int();
      for(int i = 0; i < jumlah_bola; i++) {
        bola_muncul();
      }
    }

  private:
    int score_;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr score_pub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    double waktu_;
    rclcpp::TimerBase::SharedPtr game_timer_;

    std::vector<bola> kumpulan_bola_;
    double last_time_;
    int catcher_x_ = -1, catcher_y_ = -1; 

    void callback_gambar(const sensor_msgs::msg::Image::SharedPtr gambar) {
      cv_bridge::CvImagePtr gambar_bgr;

      try {
         gambar_bgr = cv_bridge::toCvCopy(gambar, "bgr8");
      } catch(cv_bridge::Exception& err) {
        RCLCPP_ERROR(this->get_logger(), "Tidak dapat menerima frame: \n%s", err.what());
        return;
      }

      cv::Mat frame = gambar_bgr->image;
      auto hsv_lo = this->get_parameter("hsv_lower").as_integer_array();
      auto hsv_up = this->get_parameter("hsv_upper").as_integer_array();
      int min_area = this->get_parameter("min_area").as_int();

      cv::Mat hsv, mask;
      cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
      cv::inRange(hsv, cv::Scalar(hsv_lo[0], hsv_lo[1], hsv_lo[2]), cv::Scalar(hsv_up[0], hsv_up[1], hsv_up[2]), mask);

      std::vector<std::vector<cv::Point>> kontur;
      cv::findContours(mask, kontur, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

      int kontur_x = -1, kontur_y = -1;
      double max_area = 0;

      std::vector<cv::Point> luas_max;

      for(const auto& k : kontur) {
        double luas = cv::contourArea(k);
        if(luas > min_area && luas > max_area) {
          max_area = luas;
          luas_max = k;
        }
      }

      if(max_area != 0) {
        cv::Moments momen = cv::moments(luas_max);
        kontur_x = int(momen.m10 / momen.m00);
        kontur_y = int(momen.m01 / momen.m00);
        
        catcher_x_ = kontur_x;
        catcher_y_ = kontur_y;

        // cv::Rect kotak = cv::boundingRect(luas_max);
        // cv::rectangle(frame, kotak, cv::Scalar(0, 255, 0), 2);
        cv::circle(frame, cv::Point(kontur_x, kontur_y), 5, cv::Scalar(0, 0, 255), -1);
      } else {
        catcher_x_ = -1;
        catcher_y_ = -1;
      }
      
      // auto debug_msg = cv_bridge::CvImage(gambar->header, "bgr8", frame).toImageMsg();
      // image_pub_->publish(*debug_msg);
      RCLCPP_INFO(this->get_logger(), "KOORDINAT WARNA BIRU : X = %d Y = %d", kontur_x, kontur_y);    

      int radius = this->get_parameter("ball_radius").as_int();
      double waktu_sekarang = this->now().seconds();
      double patokan = this->get_parameter("hold_duration").as_double();

      for(const auto& bola : kumpulan_bola_) {
        cv::Point posisi_bola(static_cast<int>(bola.x), static_cast<int>(bola.y));
        if(bola.disentuh) {
          cv::circle(frame, cv::Point(static_cast<int>(bola.x), static_cast<int>(bola.y)), radius, cv::Scalar(0, 255, 255), -1);

          double dwaktu = waktu_sekarang - bola.sentuh_bola;

          if(dwaktu >= patokan) {
            dwaktu = patokan;
          }

          double persentase = (dwaktu / patokan) * 100;

          std::ostringstream streamObj;
          streamObj << std::fixed << std::setprecision(1) << persentase << "s%";
          std::string teks_loading = streamObj.str();

          cv::Point posisi_teks(posisi_bola.x - 30, posisi_bola.y + 5); 

          cv::putText(frame, teks_loading, posisi_teks, cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 0, 0), 3);
          cv::putText(frame, teks_loading, posisi_teks, cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(255, 255, 255), 2); 

        } else {
          cv::circle(frame, cv::Point(static_cast<int>(bola.x), static_cast<int>(bola.y)), radius, cv::Scalar(255, 0, 0), -1);
        }
      }
      
      std::string teks_skor = "Score: " + std::to_string(score_);
      cv::putText(frame, teks_skor, cv::Point(22, 52), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 0), 4);
      cv::putText(frame, teks_skor, cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(255, 255, 255), 3);

      RCLCPP_INFO(this->get_logger(), "Jumlah bola saat ini: %zu", kumpulan_bola_.size());

      cv::imshow("Kamera", frame);
      cv::waitKey(1);
    }

    void bola_muncul() {
      std::random_device rd;
      std::mt19937 gen(rd());

      std::uniform_real_distribution<> spawn_x(100.0, 540.0);
      std::uniform_real_distribution<> spawn_y(100.0, 380.0);

      std::uniform_real_distribution<> spawn_angle(0.0, 2.0 * M_PI);

      double speed = this->get_parameter("ball_speed").as_double();
      double sudut = spawn_angle(gen);

      bola ball;
      ball.x = spawn_x(gen);
      ball.y = spawn_y(gen);

      ball.kecepatan_x = speed * std::cos(sudut);
      ball.kecepatan_y = speed * std::sin(sudut);
      
      kumpulan_bola_.push_back(ball);
    }

    void update_game() {
      double now = this->now().seconds();
      double kecepatan_waktu = now - last_time_;
      last_time_ = now;

      double radius = this->get_parameter("ball_radius").as_int();

      double frame_x = 640.0;
      double frame_y = 480.0;
      
      for(auto bola = kumpulan_bola_.begin(); bola != kumpulan_bola_.end();) {
        bool sedang_menyentuh = false;
        bola->x += bola->kecepatan_x * kecepatan_waktu;
        bola->y += bola->kecepatan_y * kecepatan_waktu;

        if(bola->x - radius <= 0) {
          bola->x = radius;
          bola->kecepatan_x = std::abs(bola->kecepatan_x);
        } else if (bola->x + radius >= frame_x) {
          bola->x = frame_x - radius;
          bola->kecepatan_x = -std::abs(bola->kecepatan_x);
        }

        if(bola->y - radius <= 0) {
          bola->y = radius;
          bola->kecepatan_y = std::abs(bola->kecepatan_y);
        } else if(bola->y + radius >= frame_y) {
          bola->y = frame_y - radius;
          bola->kecepatan_y = -std::abs(bola->kecepatan_y);
        }

        if(catcher_x_ != -1 && catcher_y_ != -1) {
          double dx = bola->x - catcher_x_;
          double dy = bola->y - catcher_y_;

          double jarak = std::sqrt(dx * dx + dy * dy);

          if(jarak <= radius) {
            sedang_menyentuh = true;
          }
        }

        auto timer = this->get_parameter("hold_duration").as_double();
        bool bola_tertangkap = false;

        if(sedang_menyentuh) {
          if(!bola->disentuh) {
            bola->disentuh = true;
            bola->sentuh_bola = this->now().seconds();
          } else {
            double timer_berlangsung = this->now().seconds() - bola->sentuh_bola;
            if(timer_berlangsung >= timer) {
               bola_tertangkap = true;
               score_ += 1;
            }
          }
        } else {
          bola->disentuh = false;
        }

        if(bola_tertangkap) {
          bola = kumpulan_bola_.erase(bola);
          bola_tertangkap = false;
          bola_muncul();
        } else {
          ++bola;
        }
      }
    }
}; 

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GameNode>());
  rclcpp::shutdown();
  return 0;
}



