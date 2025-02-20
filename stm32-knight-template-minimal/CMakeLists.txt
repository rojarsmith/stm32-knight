cmake_minimum_required(VERSION 3.22)
include(ExternalProject)

# In order to use CMake for cross-compiling
set(CMAKE_CXX_COMPILER_FORCED "true") 

# Include toolchain file
include("gcc-arm-none-eabi.cmake")

# Set the project name
set(CMAKE_PROJECT_NAME stm32-knight-template-minimal)

# Core project settings
project(${CMAKE_PROJECT_NAME})

# Include external project file
include("projects.cmake")