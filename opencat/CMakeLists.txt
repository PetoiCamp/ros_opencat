cmake_minimum_required(VERSION 3.5)
project(opencat)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(type_description_interfaces REQUIRED)
find_package(opencat_msgs REQUIRED)
find_package(rclcpp REQUIRED)

# Create a library or executable
add_library(${PROJECT_NAME} src/opencat/opencat.cpp)

ament_target_dependencies(${PROJECT_NAME}
  type_description_interfaces
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
  rclcpp
  # type_description_interfaces
)

# Include directories
include_directories(include)
include_directories(${rclcpp_INCLUDE_DIRS})
include_directories(${opencat_msgs_INCLUDE_DIRS})

# Export the targets
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(rosidl_default_generators)

# Install the library and headers
install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# Testing configuration
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
