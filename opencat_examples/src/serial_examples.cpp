#include "opencat_serial/opencat_serial.hpp"
#include "opencat_serial/serial.hpp"

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

    // connect to first port available
    OpenCat::Robot rob(serial_ports[0]);
    std::cout << "start executing tasks..." << std::endl;
    rob.SendTask({OpenCat::Command::BALANCE, 5});
    return 0;
}
