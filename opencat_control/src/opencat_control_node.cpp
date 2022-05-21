#include "ros/ros.h"
#include "serial.hpp"

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "opencat_control_node");
  Serial serial("/dev/ttyUSB0", B115200);
  return 0;
}
