/**
 * @brief Serial library for opencat
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#ifndef OPENCAT_SERIAL_H_
#define OPENCAT_SERIAL_H_
#include "opencat_serial/serial.hpp"
#include "opencat/opencat.hpp"
#include <string>
#include <vector>

using std::vector;

namespace OpenCat
{
/**
 * @brief wrapper class to communicate with OpenCat robot
 * @inherit ::Serial::Serial, protected as we don't need to send arbitrary data
 **/
class Robot : protected ::Serial::Serial
{
  public:
    /**
     * @brief default constructor
     * @param serial_port: serial port to connect the dog
     **/
    Robot(string serial_port);

    /**
     * @brief send task to robot
     * @param task: %Task data pack
     * @return response message from robot
     **/
    std::string SendTask(const Task &task, bool verbose = false);

    void SendMultipleTasks(const vector<Task> &tasks, bool verbose=false);

  protected:
    static const speed_t BAUD_RATE = B115200;
};
} // namespace OpenCat

#endif // OPENCAT_SERIAL_H_
