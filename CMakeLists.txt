cmake_minimum_required(VERSION 3.0.2)
project(rvo2_ros)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES rvo2_ros
 CATKIN_DEPENDS roscpp rospy std_msgs tf
 DEPENDS system_lib
)

include_directories(
  include
  include/${PROJECT_NAME}
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/Agent.cc
  src/${PROJECT_NAME}/Export.cc
  src/${PROJECT_NAME}/KdTree.cc
  src/${PROJECT_NAME}/Line.cc
  src/${PROJECT_NAME}/Obstacle.cc
  src/${PROJECT_NAME}/RVOSimulator.cc
  src/${PROJECT_NAME}/Vector2.cc
)

add_dependencies(${PROJECT_NAME} 
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

add_executable(agent_viz src/example/agent_viz.cpp)
target_link_libraries(agent_viz ${catkin_LIBRARIES} ${PROJECT_NAME})