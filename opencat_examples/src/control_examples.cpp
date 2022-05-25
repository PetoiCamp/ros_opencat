#include "opencat_control/control_srv.h"
#include "opencat_serial/opencat_serial.hpp"
#include "ros/node_handle.h"
#include "ros/ros.h"

using opencat_control::control_srv;
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "opencat_ros_client_example");
    ros::NodeHandle nh;
    ros::ServiceClient sendTask =
        nh.serviceClient<control_srv>("opencat_send_task");
    control_srv srv;
    srv.request.cmd = OpenCat::Command::CALIB_POSE;
    srv.request.delay = 2;
    sendTask.call(srv);
}
