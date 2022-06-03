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
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <thread>

namespace OpenCat
{
Robot::Robot(string serial_port) : ::serial::Serial(serial_port, 115200)
{
    // wait for robot to boot up
    using std::chrono::seconds;
    std::this_thread::sleep_for(seconds(5));
    this->read(999);
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
    this->write(data);
    // delay as requested
    std::this_thread::sleep_for(milliseconds(size_t(task.delay * 1000)));
    // get string
    return this->read(999);
}

void Robot::SendMultipleTasks(const vector<Task> &tasks, bool verbose)
{
    for (auto &task : tasks)
    {
        this->SendTask(task, verbose);
    }
}

const vector<string> ListSerialPorts()
{
    const string tty_path = "/sys/class/tty";
    DIR *dir;
    dirent *ent;
    dir = opendir(tty_path.c_str());
    vector<string> res;
    if (dir != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr)
        {
            string tty_name = string(ent->d_name);
            string device_path = tty_path + "/" + tty_name + "/" + "device";
            if (access(device_path.c_str(), F_OK) == 0)
            {
                char sym_link[256] = "";
                readlink(device_path.c_str(), sym_link, 256);
                // possible that pointing to the driver
                if (string(sym_link) != "../../../serial8250")
                {
                    res.push_back("/dev/" + tty_name);
                }
            }
        }
        closedir(dir);
    }
    else
    {
        std::cerr << "Error: Getting serial ports failed" << std::endl;
    }
    return res;
}
} // namespace OpenCat
