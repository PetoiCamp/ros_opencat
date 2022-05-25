#include "opencat_server/opencat_server.hpp"
#include "opencat_serial/opencat_serial.hpp"

namespace OpenCat
{
ROSRobot::ROSRobot(std::string serial_port) : rob(serial_port)
{
}

bool ROSRobot::primitive_service_handler(base_task::Request &req,
                                         base_task::Response &res)
{
    Task tsk = {(Command)req.cmd, TaskArgs(req.arguments), req.delay};
    rob.SendTask(tsk);
    res.res = true;
    return true;
}
} // namespace OpenCat
