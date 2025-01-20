cmake_minimum_required(VERSION 3.14)
project(topic_state_monitor)

find_package(autoware_cmake REQUIRED)
autoware_package()

find_package(agnocastlib REQUIRED)

ament_auto_add_library(topic_state_monitor SHARED
  src/topic_state_monitor/topic_state_monitor.cpp
  src/topic_state_monitor_core.cpp
)

ament_target_dependencies(topic_state_monitor agnocastlib)
target_include_directories(topic_state_monitor PRIVATE
  ${agnocastlib_INCLUDE_DIRS}
)

rclcpp_components_register_node(topic_state_monitor
  PLUGIN "topic_state_monitor::TopicStateMonitorNode"
  EXECUTABLE topic_state_monitor_node
)

ament_auto_package(INSTALL_TO_SHARE
  launch
)
