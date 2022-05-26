# ros_opencat

control opencat robots using ROS.

## Description
+ `opencat_serial` - serial library for OpenCat implemented in C++
+ [ ] `opencat_server` - ros interface for controlling OpenCat
+ `opencat_examples` - demo programs on how to use the project
+ [ ] `opencat_description` - mesh and model files

## Usage
### Install
In `src` directory, run
``` sh
git clone https://github.com/TomCC7/ros_opencat
cd ..
catkin_make
source ./devel/setup.sh
```

### Examples
+ using serial library
``` sh
rosrun opencat_examples opencat_examples_serial
```
+ using ros service

``` sh
# start core
roscore
# start service server
rosrun opencat_server opencat_service_node
# examples using oppencat ros service in C++
rosrun opencat_examples opencat_examples_client_cpp
# examples using opencat ros service in python
rosrun opencat_examples opencat_examples_client_py
```
