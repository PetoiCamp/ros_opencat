#ifndef OPENCAT_CONTROL_H_
#define OPENCAT_CONTROL_H_
#include "opencat/srv/base_task.hpp"
#include "opencat_serial/opencat_serial.hpp"
#include <opencat/srv/detail/base_task__struct.hpp>
#include <string>
#include <vector>
using namespace opencat::srv;
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
    bool primitive_service_handler(
        const std::shared_ptr<BaseTask_Request> request,
        std::shared_ptr<BaseTask_Response> response);

  protected:
    // serial interface
    Robot rob;
};

// bool send_command(Command cmd, );

} // namespace OpenCat

#endif // OPENCAT_CONTROL_H_
