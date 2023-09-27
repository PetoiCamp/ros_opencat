# [Petoi](https://www.petoi.com/ "Petoi")  

### Bittle ROS Documentation 
This documentation is designed to configure Bittle in the ROS Simulation Environment.

### Pre-requisites 🤔
Your system must have:
- [Ubuntu (Version 20.04 recommended)](https://releases.ubuntu.com/focal/)
- [ROS Noetic Ninjemys](http://wiki.ros.org/noetic/Installation/Ubuntu)

### Tutorial 😃
- #### [ROS Installation Steps](https://www.youtube.com/watch?v=ZA7u2XPmnlo)
  
   Open the terminal and follow the below commands to install [ROS Noetic Ninjemys](http://wiki.ros.org/noetic/Installation/Ubuntu)

 
```bash
    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
 ```
 ```bash
    sudo apt install curl # if you haven't already installed curl
 ```
```bash
 curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add - 
```
```bash
sudo apt update
```
```bash 
sudo apt install ros-noetic-desktop-full
```
- #### Create Catkin Workspace for the ROS Packages
  

Follow the below mentioned commands to create a Catkin Workspace for creating and modifying the ROS packages. 

```bash 
mkdir -p ~/catkin_ws/src
```
```bash 
cd ~/catkin_ws/
```
```bash 
catkin_make
```
Open the ```~/.bashrc file``` via below command 

```bash 
gedit ~/.bashrc
```
.bashrc file will appear

<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/bashrc.png " height ="100%" width="100%" alt text="bashrc file">

Paste the below commands in ```.bashrc file``` (screenshot has been attached for reference)

```bash 
source /opt/ros/noetic/setup.bash
source ~/catkin_ws/devel/setup.bash
```
Clone the folder [bittle_description package](https://github.com/garrykasprov/Petoi_ROS_Documentation/tree/main/bittle_ros) and paste it inside the ```src``` folder of the catkin workspace.

Start the ROS master via
```bash
roscore
```

<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/roscore.png">

Open a new terminal window or simply press ```Ctrl+Alt+T```and follow below mentioned commands to spawn your Bittle in an empty Gazebo Simulation Environment.

```bash
roscd bittle_description
```
``` bash
ls
```
```bash
cd launch
```
```bash
ls
```
```bash
roslaunch bittle_description gazebo.launch
```
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/final.png">
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/bittle_simulation.png">

- #### Steps to launch your Bittle in the Gazebo world Simulation Environment
  <br>

$${\color{red}CAUTION: \space \color{orange}Before \space launching \space your \space Bittle \space in \space the \space Gazebo \space World \space Simulation \space Environment \space you \space are \space first \space required \space to \space kill \space the \space existing }$$

$${\color{orange}processes. \space Just \space by \space simply \space pressing \space Ctrl+C \space it \space will \space going \space to \space kill \space the \space existing \space node}$$

<br>
   Once the existing nodes are killed follow the below commands to launch your bittle.

  ```bash
  roslaunch bittle_gazebo bittle_world.launch
  ```
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/bittle_world.png">

For launching controller for the joints of the Bittle.

```bash
  roslaunch bittle_description controller.launch
  ```
Press the play button ▶️ in the Gazebo to load all the joint controllers.
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/controller_1.png">
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/controller_2.png">

For controlling the joint position of the neck you are required to install [joystick ros driver](http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick) <br>
[Video reference for installation of joystick driver](https://www.youtube.com/watch?v=4cSRdS83PX4&t=204s)

Open a new terminal window and launch your joystick package
```bash
  roslaunch bittle_joystick bittle_joystick.launch
  ```
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/joystick_2.png">

Open another terminal and run your joystick node 
```bash
  rosrun bittle_joystick bittle_joystick.py
  ```
Press `Enter`

<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/joystick_1.jpeg">
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/joystick.jpeg">

Move this joystick button as mentioned in the above image to control the neck movement.

To visualize your Bittle in Rviz(Robot Visualization) 

```bash
   roslaunch bittle_description display.launch
  ```
<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/rviz.png">

Open a new terminal to publish the joint angles for the different joints of the Bittle.
```bash
   rosrun bittle_description joint_controller.py
  ```
You can move the joints by sliding the corresponding joints bar using `joint_state_publisher_gui` node.

<img src="https://github.com/garrykasprov/Petoi_ROS_Documentation/blob/main/bittle_ros_images/bittle.gif" height="35%">


### Yayy!! You are done😃 

