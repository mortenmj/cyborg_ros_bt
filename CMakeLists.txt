cmake_minimum_required(VERSION 2.8.3)
project(cyborg_bt)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package( catkin REQUIRED COMPONENTS
    genmsg
	actionlib_msgs
	actionlib
	message_generation
	roscpp
    roslib
	rospy
	std_msgs
    behavior_tree_core
    roslaunch
)
roslaunch_add_file_check(launch)

add_action_files(
	DIRECTORY action
)

add_service_files(
    DIRECTORY srv
)

#generate_messages( DEPENDENCIES 
#	std_msgs
#	actionlib_msgs
#)

add_definitions(-Wall -lglut -lGL -std=c++11)

catkin_install_python( PROGRAMS
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS 
	roscpp
	rospy
	std_msgs
	message_runtime
	actionlib_msgs
    behavior_tree_core
)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# FIND GTest
#########################################################
find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(include
    ${catkin_INCLUDE_DIRS} )

add_executable(cyborg_tree src/main.cpp src/parser.cpp)

target_link_libraries(cyborg_tree
    behavior_tree_core
    ${catkin_LIBRARIES}
)

add_dependencies(cyborg_tree
    ${PROJECT_NAME}_generate_messages_cpp
    behavior_tree_core_generate_messages_cpp
)
