/**
 * @brief source file for opencat_serial lib
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#include "opencat_serial/opencat_serial.hpp"
#include <chrono>

namespace OpenCat
{
Robot::Robot(string serial_port) : ::Serial::Serial(serial_port, BAUD_RATE)
{
    // wait for robot to boot up
    using std::chrono::seconds;
    std::this_thread::sleep_for(seconds(5));
}

std::string Robot::SendTask(const Task task)
{
    using std::chrono::milliseconds;
    string cmd_name = command_name[task.cmd];
    vector<uint8_t> data(cmd_name.begin(), cmd_name.end());
    // no extra arguments
    if (task.arguments.empty())
    {
        // cli commands
        if (data[0] == 'k')
        {
            data.push_back('\n');
        }
    }
    else
    {
        std::cout << "task currently not implemented" << std::endl;
    }
    this->send(data);
    // delay as requested
    std::this_thread::sleep_for(milliseconds(size_t(task.delay * 1000)));
    return "TODO: change this";
}
} // namespace OpenCat
