# ros_opencat

control opencat robots using ROS.

## Description
+ `opencat_serial` - serial library for OpenCat implemented in C++
+ [ ] `opencat_control` - ros interface for controlling OpenCat
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
After sourcing the setup file, run
``` sh
rosrun opencat_examples opencar_examples_serial
```
