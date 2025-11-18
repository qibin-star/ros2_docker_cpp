cmake_minimum_required(VERSION 3.8)
project(cpp_ws_demo)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# nlohmann_json 是 header-only，通常不需要 find_package
# 如果你想更规范，也可以尝试：
# find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
# 如果使用 find_package(nlohmann_json)，可以加：
# target_link_libraries(talker nlohmann_json::nlohmann_json)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
# target_link_libraries(listener nlohmann_json::nlohmann_json)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

