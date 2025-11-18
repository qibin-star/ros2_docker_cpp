#!/bin/bash
set -e

# 1. source ROS2 环境和工作空间
source /opt/ros/humble/setup.bash
source /ros2_ws/install/setup.bash

# 2. 启动 C++ talker 和 listener
ros2 run cpp_ws_demo talker &
ros2 run cpp_ws_demo listener &

# 3. 启动 rosbridge websocket（9090）
ros2 launch rosbridge_server rosbridge_websocket_launch.xml
