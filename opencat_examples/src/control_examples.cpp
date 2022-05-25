#include "opencat/base_task.h"
#include "opencat/opencat.hpp"
#include "ros/node_handle.h"
#include "ros/ros.h"

using opencat::base_task;
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "opencat_ros_client_example");
    ros::NodeHandle nh;
    ros::ServiceClient sendTask =
        nh.serviceClient<base_task>("opencat_send_task");
    base_task srv;
    srv.request.cmd = OpenCat::Command::CALIB_POSE;
    srv.request.delay = 2;
    sendTask.call(srv);
}
