#ifndef OPENCAT_CONTROL_H_
#define OPENCAT_CONTROL_H_
#include "opencat_control/control_srv.h"
#include <string>
#include <vector>
using opencat_control::control_srv;
using std::vector;

namespace OpenCat
{
/**
 * @brief handle primitive RPC service call and send command to OpenCat
 * @param req: %Request received
 * @param res: %Response to be sent
 **/
bool primitive_service_handler(control_srv::Request &req,
                               control_srv::Response &res);

// bool send_command(Command cmd, );

} // namespace OpenCat

#endif // OPENCAT_CONTROL_H_
