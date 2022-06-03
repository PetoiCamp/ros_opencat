# ros_opencat

Control robots powered by [OpenCat](https://github.com/PetoiCamp/OpenCat) using [ROS](https://www.ros.org/).

## Description
+ `opencat_serial` - serial library for OpenCat implemented in C++
+ `opencat_server` - ROS interface for controlling OpenCat
+ `opencat_examples` - demo programs on how to use the project
+ [ ] `opencat_description` - mesh and model files

## Usage
### Install

**NOTE**: due to multi-threading in make process, `catkin_make` may fail, in that case just rerun the command multiple times.

Make sure you have installed ROS and can run `catkin_make`. In `src` directory, run
``` sh
git clone https://github.com/TomCC7/ros_opencat
cd ros_opencat
# clone serial lib
git submodule init
git submodule update
cd ../..
catkin_make
source ./devel/setup.sh
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
-it --rm --privileged --network host --name ros ros:noetic-robot
```

+ source files and build inside the container

```bash
cd /workspace
source /opt/ros/noetic/setup.bash
catkin_make
source devel/setup.bash
```

+ run examples (see [Examples](#Examples]) more more)

```bash
rosrun opencat_examples opencat_examples_serial
```



### Multiple Machines ([ref](http://wiki.ros.org/ROS/Tutorials/MultipleMachines))

Ros is designed with distributed computing in mind. Here's a simple example on how to run nodes on different machines.

+ on host machine (usually more powerful than Raspberry Pi)

```bash
# launch server
roscore
```

+ run service node on Raspberry Pi

```bash
export ROS_MASTER_URI=http://<Host_IP>:11311/
rosrun opencat_server opencat_service_node
```

+ send command from host

```bash
rosrun opencat_examples opencat_examples_client_cpp
```



## Examples
+ using serial library
``` sh
rosrun opencat_examples opencat_examples_serial
```
+ using ROS service

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



## Dependency

+ [serial](https://github.com/wjwwood/serial) - a C++ serial library compatible with ROS
