/**
 * @brief source file for opencat_serial lib
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#include "opencat_serial/opencat_serial.hpp"

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
    }
    else
    {
        if (islower(data[0]) && data[0] != 'c')
        {
            std::cout << "task currently not implemented" << std::endl;
            exit(-1);
        }
        std::copy(task.arguments.begin(), task.arguments.end(),
                  std::back_inserter(data));
    }

    // different end character for cli and binary call
    if (islower(data[0]))
    {
        data.push_back('\n');
    }
    else
    {
        data.push_back('~');
    }
    this->send(data);
    // delay as requested
    std::this_thread::sleep_for(milliseconds(size_t(task.delay * 1000)));
    return "TODO: change this";
}
} // namespace OpenCat
