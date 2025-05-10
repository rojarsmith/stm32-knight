cmake_minimum_required(VERSION 3.28)

message("   CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# In order to use CMake for cross-compiling
# The compiler configuration was forced by the user.
# Assume the user has configured all compiler information.
set(CMAKE_CXX_COMPILER_FORCED true)

# Include toolchain file
include("gcc-arm-none-eabi.cmake")

# Set the project name
set(CMAKE_PROJECT_NAME stm32-knight-touchgfx-ew2017)

# Core project settings
project(${CMAKE_PROJECT_NAME})

# Include external project file
include("projects.cmake")
