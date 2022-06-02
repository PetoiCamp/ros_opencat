/**
 * @brief source file for opencat_serial lib
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#include "opencat_serial/opencat_serial.hpp"
#include "opencat/opencat_data.hpp"
#include <cassert>
#include <chrono>
#include <thread>

namespace OpenCat
{
Robot::Robot(string serial_port) : ::Serial::Serial(serial_port, BAUD_RATE)
{
    // wait for robot to boot up
    using std::chrono::seconds;
    std::this_thread::sleep_for(seconds(5));
    // auto aba = this->receive(81);
    // for (auto c:aba)
    //     std::cout << (int)c << std::endl;
}

std::string Robot::SendTask(const Task &task, bool verbose)
{
    using std::chrono::milliseconds;
    string cmd_name = command_name[task.cmd];
    vector<uint8_t> data(cmd_name.begin(), cmd_name.end());
    // no extra arguments
    if (!task.arguments.empty())
    {
        if (islower(data[0]) && data[0] != 'c')
        {
            std::cout << "task currently not implemented" << std::endl;
            exit(-1);
        }
        data.reserve(data.size() + task.arguments.size() + 1);
        for (auto arg : task.arguments)
        {
            data.push_back((uint8_t)arg);
        }
    }

    // special checks
    if (data[0] == 'L')
    {
        assert(task.arguments.size() == 16);
    }
    // different end character for cli and binary call
    switch (data[0])
    {
    case 'T':
    case 'M':
        break;
    case 'L':
    case 'I':
    case 'B':
    case 'K':
        data.push_back('~');
        break;
    // all lower bits
    default:
        data.push_back('\n');
    }
    if (verbose)
    {
        std::cout << "Start executing: " << command_description[task.cmd]
                  << std::endl;
    }
    this->send(data);
    // delay as requested
    std::this_thread::sleep_for(milliseconds(size_t(task.delay * 1000)));
    // get string
    this->receive(1);
    return "aba";
}

void Robot::SendMultipleTasks(const vector<Task> &tasks, bool verbose)
{
    for (auto &task : tasks)
    {
        this->SendTask(task, verbose);
    }
}
} // namespace OpenCat
