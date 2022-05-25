#include "opencat_server/opencat_server.hpp"
#include "opencat_serial/opencat_serial.hpp"
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    auto serial_ports = Serial::ListSerialPorts();
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
    ros::init(argc, argv, "opencat_control_node");
    ros::NodeHandle node_handle;

    ros::ServiceServer service = node_handle.advertiseService(
        "opencat_send_task", &OpenCat::ROSRobot::primitive_service_handler, &rosbot);
    ROS_INFO("Ready to receive command");
    ros::spin();
    return 0;
}
