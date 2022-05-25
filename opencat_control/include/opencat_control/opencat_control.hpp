#ifndef OPENCAT_CONTROL_H_
#define OPENCAT_CONTROL_H_
#include "opencat/base_task.h"
#include "opencat_serial/opencat_serial.hpp"
#include <string>
#include <vector>
using opencat::base_task;
using std::vector;

namespace OpenCat
{
/**
 * @brief ROS Interface Wrapper
 **/
class ROSRobot
{
  public:
    /**
     * @brief default constructor
     **/
     ROSRobot(std::string serial_port);

    /**
     * @brief handle primitive RPC service call and send command to OpenCat
     * @param req: %Request received
     * @param res: %Response to be sent
     **/
    bool primitive_service_handler(base_task::Request &req,
                                   base_task::Response &res);
    protected:
        // serial interface
        Robot rob;
};

// bool send_command(Command cmd, );

} // namespace OpenCat

#endif // OPENCAT_CONTROL_H_
