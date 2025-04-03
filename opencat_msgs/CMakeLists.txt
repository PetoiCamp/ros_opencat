cmake_minimum_required(VERSION 3.5)
project(opencat_msgs)

# Find dependencies for building the package
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)

# Generate the messages and services from the .srv files
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/BaseTask.srv"  # Define the BaseTask service
  DEPENDENCIES std_msgs  # List any additional dependencies, like std_msgs
)

# Export dependencies to other packages that depend on this one
ament_export_dependencies(rosidl_default_runtime)

# Install the service definitions
install(DIRECTORY srv
  DESTINATION share/${PROJECT_NAME}/srv
)

# Declare this as an ament package
ament_package()
