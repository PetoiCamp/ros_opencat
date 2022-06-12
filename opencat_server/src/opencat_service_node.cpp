#include "opencat_server/opencat_server.hpp"
#include "rclcpp/rclcpp.hpp"

#include <memory>

int main(int argc, char *argv[])
{
    using namespace std::placeholders;
    auto serial_ports = OpenCat::ListSerialPorts();
    if (serial_ports.empty())
    {
        std::cerr << "no serial port detected! aborting" << std::endl;
        exit(-1);
    }
    std::cout << "detected serial ports:" << std::endl;
    for (auto &port : serial_ports)
    {
        std::cout << port << std::endl;
    }
    OpenCat::ROSRobot rosbot(serial_ports[0]);

    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node =
        rclcpp::Node::make_shared("opencat_control_node");

    auto service = node->create_service<BaseTask>(
        "opencat_send_task",
        std::bind(&OpenCat::ROSRobot::primitive_service_handler, &rosbot, _1,
                  _2));

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to receive commands.");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
