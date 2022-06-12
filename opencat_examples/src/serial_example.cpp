#include "opencat_serial/opencat_serial.hpp"
#include <iostream>
using namespace OpenCat;

const vector<int16_t> pee{
    -4, 0,  10,  1,  2,   3,  3,  30,  20, 0,   0,  15, -10, 60, -10,
    40, 40, 90,  45, 10,  60, 70, 45,  6,  0,   0,  0,  45,  20, 0,
    0,  15, -10, 60, -10, 60, 53, 115, 60, -30, 40, 50, 21,  2,  10,
    0,  0,  30,  20, 0,   0,  15, -10, 60, -10, 40, 40, 90,  45, 10,
    50, 70, 45,  16, 0,   0,  0,  30,  20, 0,   0,  15, -10, 60, -10,
    40, 40, 103, 45, 10,  50, 80, 45,  16, 0,   0,  0,
};

const OpenCat::TaskArgs music{
    20, 4,  22, 4,  24, 4,  15, 4,  20, 4,  22, 8,  24, 1,  22, 4,  20, 4,  22,
    4,  27, 4,  27, 4,  27, 4,  27, 2,  20, 4,  19, 4,  20, 4,  20, 4,  20, 4,
    20, 4,  20, 2,  19, 4,  20, 4,  19, 4,  20, 4,  19, 4,  17, 4,  15, 2,  15,
    4,  15, 4,  17, 4,  17, 4,  17, 4,  17, 4,  17, 2,  15, 4,  12, 4,  15, 4,
    12, 4,  15, 4,  22, 4,  20, 2,  -1, 4,  15, 4,  24, 4,  24, 4,  24, 4,  25,
    4,  27, 4,  20, 4,  20, 4,  24, 4,  22, 1,  22, 1,  -1, 2};

std::vector<OpenCat::Task> tasks{
    {OpenCat::Command::BALANCE, 2},
    // built-in skill
    {OpenCat::Command::CHECK_AROUND, 3},
    // play joint change in sequence
    {OpenCat::Command::MOVE_JOINT_SEQUENCE,
     OpenCat::TaskArgs{0, 30, 0, -30, 0, 30, 0, -30}, 3},
    // set joints simultaneously
    {OpenCat::Command::MOVE_JOINTS_SIMULTANEOUS,
     OpenCat::TaskArgs{0, 30, 12, 0, 13, 0, 14, 0, 15, 0}, 4},
    // set all joints at once
    {OpenCat::Command::SET_JOINTS, OpenCat::TaskArgs(16, 0), 3},
    // play custom defined skill
    {OpenCat::Command::PLAY_CUSTOM_SKILL, pee, 4},
    // REPEAT_SKILL calls the last temp skill data of the CUSTOM_SKILL
    {OpenCat::REPEAT_SKILL, 4},
    // play built in melody
    {OpenCat::Command::PLAY_MELODY, 6},
    // play da jia yi qi xue mao jiao
    {OpenCat::Command::PLAY_CUSTOM_SOUND, music, 15},
    {OpenCat::SHUT_DOWN, 2}};

int main()
{
    auto serial_ports = OpenCat::ListSerialPorts();
    if (serial_ports.empty())
    {
        std::cerr << "no serial port detected! aborting" << std::endl;
        exit(-1);
    }
    std::cout << "detected serial ports:" << std::endl;
    for (auto &port:serial_ports)
    {
        std::cout << port << std::endl;
    }
    // connect to first port available
    OpenCat::Robot rob(serial_ports[0]);
    std::cout << "start executing tasks..." << std::endl;
    // easier to stand
    rob.SendTask({OpenCat::Command::CALIB_POSE, 2}, true);
    // sending multiple task
    rob.SendMultipleTasks(tasks, true);
    std::cout << "Demo finished!" << std::endl;
    return 0;
}
