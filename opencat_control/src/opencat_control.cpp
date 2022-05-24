#include "opencat_control/opencat_control.hpp"
#include "opencat_serial/opencat_serial.hpp"

namespace OpenCat
{
ROSRobot::ROSRobot(std::string serial_port) : rob(serial_port)
{
}

bool ROSRobot::primitive_service_handler(control_srv::Request &req,
                                         control_srv::Response &res)
{
    Task tsk = {(Command)req.cmd, TaskArgs(req.arguments), req.delay};
    rob.SendTask(tsk);
    res.res = true;
    return true;
}
} // namespace OpenCat
