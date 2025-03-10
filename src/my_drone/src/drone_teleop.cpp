#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <termios.h>
#include <iostream>

class DroneTeleop : public rclcpp::Node {
public:
    DroneTeleop() : Node("drone_teleop") {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        run();
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    void run() {
        char key;
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        geometry_msgs::msg::Twist twist;
        std::cout << "Use WASD to move the drone. Press 'q' to quit.\n";

        while (rclcpp::ok()) {
            std::cin >> key;
            twist.linear.x = (key == 'w') - (key == 's');
            twist.linear.y = (key == 'a') - (key == 'd');
            twist.linear.z = (key == 'r') - (key == 'f');
            publisher_->publish(twist);
            if (key == 'q') break;
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DroneTeleop>());
    rclcpp::shutdown();
    return 0;
}
