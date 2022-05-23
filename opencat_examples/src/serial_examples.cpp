#include "opencat_serial/opencat_serial.hpp"
#include "opencat_serial/serial.hpp"

int main(int argc, char * argv[])
{
    auto serial_ports = Serial::ListSerialPorts();
    std::cout << "detected serial ports:" << std::endl;
    for (auto & port: serial_ports )
    {
        std::cout << port << std::endl;
    }
    return 0;
}
