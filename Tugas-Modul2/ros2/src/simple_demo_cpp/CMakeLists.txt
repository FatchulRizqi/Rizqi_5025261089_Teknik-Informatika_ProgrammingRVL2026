# cmake_minimum_required(VERSION 3.8)
# project(simple_demo_cpp)
#
# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()
#
# # find dependencies
# find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(std_msgs REQUIRED)
# find_package(package_messages REQUIRED)
#
# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # comment the line when a copyright and license is added to all source files
#   set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # comment the line when this package is in a git repo and when
#   # a copyright and license is added to all source files
#   set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()
#
# ament_package()
#
# # Talker Executable
# add_executable(talker src/talker.cpp)
# ament_target_dependencies(talker
#   rclcpp
#   std_msgs
# )
#
# # Listener Executable
# add_executable(listener src/listener.cpp)
# ament_target_dependencies(listener
#   rclcpp
#   std_msgs
# )
#
# # Install Rules
# install(TARGETS
#   talker
#   listener
#   DESTINATION lib/${PROJECT_NAME}
# )

cmake_minimum_required(VERSION 3.8) 
project(simple_demo_cpp) 

if(NOT CMAKE_CXX_STANDARD) 
  set(CMAKE_CXX_STANDARD 14) 
endif() 

find_package(ament_cmake REQUIRED) 
find_package(rclcpp REQUIRED) 
find_package(custom_message REQUIRED)   
find_package(std_msgs REQUIRED) 

add_executable(talker src/talker.cpp) 
ament_target_dependencies(talker rclcpp std_msgs custom_message) 

add_executable(listener src/listener.cpp) 
ament_target_dependencies(listener rclcpp std_msgs custom_message) 

install(TARGETS talker listener DESTINATION lib/${PROJECT_NAME}) 
ament_package()
