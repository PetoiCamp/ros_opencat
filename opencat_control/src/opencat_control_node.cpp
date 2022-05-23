#include "ros/ros.h"
#include "opencat_control/opencat_control.hpp"


int main(int argc, char *argv[]) {
  ros::init(argc, argv, "opencat_control_node");
  ros::NodeHandle node_handle;

  // ros::ServiceServer service =
  //     node_handle.advertiseService("control_cat", Controller::send_command);
  ROS_INFO("Ready to receive command");
  return 0;
}
