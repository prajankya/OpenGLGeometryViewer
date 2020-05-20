#
# Set minimum required version
#
cmake_minimum_required(VERSION 3.5)

project(opengl_viewer LANGUAGES CXX)


#
# add path where cmake files must be searched for
#
#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


#
# Include path points to the base source dir
#
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})


# Get New OpenGL libraries
if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()


#
# Dependencies
#

# OpenGL
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL included at ${OPENGL_INCLUDE_DIR}")
include_directories(${OPENGL_INCLUDE_DIRS})

# GLUT
find_package(GLUT REQUIRED)
message(STATUS "GLUT included at ${GLUT_INCLUDE_DIR}")
include_directories(${GLUT_INCLUDE_DIR})

# # GLM
# find_package(GLM REQUIRED)
# message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
# include_directories(${GLM_INCLUDE_DIR})

# # GLFW
# find_package(GLFW3 REQUIRED)
# message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
# include_directories(${GLM_INCLUDE_DIR})


#
# Compile to executable
#
add_executable(opengl_viewer src/viewer.cpp)

target_link_libraries(opengl_viewer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# target_link_libraries(footbot_diffusion
#   argos3core_simulator
#   argos3plugin_${ARGOS_BUILD_FOR}_footbot
#   argos3plugin_${ARGOS_BUILD_FOR}_genericrobot)
