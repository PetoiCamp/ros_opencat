# ros_opencat

Control robots powered by [OpenCat](https://github.com/PetoiCamp/OpenCat) using [ROS2](https://www.ros.org/). There's also a ROS1 branch [here](https://github.com/TomCC7/ros_opencat/tree/ros1).

## Description
+ `opencat_serial` - serial library for OpenCat implemented in C++
+ `opencat_server` - ROS interface for controlling OpenCat
+ `opencat_examples` - demo programs on how to use the project
+ [ ] `opencat_description` - mesh and model files

## Usage
### Install

Make sure you have installed ROS and can run `colcon`. In `src` directory, run
``` sh
git clone https://github.com/TomCC7/ros_opencat
cd ros_opencat
# clone serial lib
git submodule init
git submodule update
cd ../..
colcon build
source ./install/setup.bash
```

### Using ROS on Raspberry Pi

Currently, it's recommended to install ROS using docker.

+ install docker on Raspberry Pi ([ref](https://phoenixnap.com/kb/docker-on-raspberry-pi))

```bash
sudo apt-get update && sudo apt-get upgrade
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo usermod -aG docker pi
# test installation
docker run hello-world
```

+ prepare workspace

```bash
mkdir -p workspace/src
cd workspace/src
git clone https://github.com/TomCC7/ros_opencat
cd ros_opencat
git submodule init && git submodule update
cd ../../..
```

+ run the container

```bash
docker run -v path/to/workspace:/workspace \
-it --rm --privileged --network host --name ros ros:foxy-robot
```

+ source files and build inside the container

```bash
cd /workspace
source /opt/ros/noetic/setup.bash
colcon build
source devel/setup.bash
```

+ run examples (see [Examples](#Examples]) more more)

```bash
ros2 run opencat_examples opencat_examples_serial
```



### Multiple Machines ([ref](http://wiki.ros.org/ROS/Tutorials/MultipleMachines))
TODO


## Examples
+ using serial library
``` sh
ros2 run opencat_examples opencat_examples_serial
```
+ using ROS service

``` sh
# start service server
ros2 run opencat_server opencat_service_node
# examples using oppencat ros service in C++
ros2 run opencat_examples opencat_examples_client_cpp
# examples using opencat ros service in python
ros2 run opencat_examples opencat_examples_client_py
```



## Dependency

+ [serial](https://github.com/wjwwood/serial) - a C++ serial library compatible with ROS
