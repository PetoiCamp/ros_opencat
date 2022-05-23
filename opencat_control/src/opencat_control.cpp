#include "opencat_control/opencat_control.hpp"

namespace OpenCat
{
bool primitive_service_handler(control_srv::Request &req, control_srv::Response &res)
{
    return true;
}

// bool send_command(control_srv::Request &req, control_srv::Response &res)
// {
//     switch (req.command)
//     {
//         case CALIBRATE:
//         case MOVE_JOINTS:
//         case SET_JOINTS:
//     }
//     return true;
// }

}
