#include "opencat_server/opencat_server.hpp"
#include "opencat_serial/opencat_serial.hpp"

namespace OpenCat
{
ROSRobot::ROSRobot(std::string serial_port) : rob(serial_port)
{
}

bool ROSRobot::primitive_service_handler(
        const std::shared_ptr<BaseTask_Request> req,
        std::shared_ptr<BaseTask_Response> res)
{
    Task tsk = {(Command)req->cmd, TaskArgs(req->arguments), req->delay};
    rob.SendTask(tsk);
    res->res = true;
    return true;
}
} // namespace OpenCat
