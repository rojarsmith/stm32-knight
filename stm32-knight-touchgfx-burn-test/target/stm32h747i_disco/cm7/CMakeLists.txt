cmake_minimum_required(VERSION 3.28)
message("[target/stm32h747i_disco/core0/CMakeLists.txt]")
message("   BUILD_CONTEXT: " ${BUILD_CONTEXT})

if(${BUILD_CONTEXT} MATCHES .*APP_*)
    message("   FREERTOS_KERNEL_PATH=" ${FREERTOS_KERNEL_PATH})
    set(CMSIS_RTOS_V2 ../../../../stm32-knight-sdk/operatingsystem/CMSIS_RTOS_V2)
    set(TOUCHGFX_PATH ../../../../stm32-knight-sdk/firmware/Middlewares/ST/TouchGFX)
endif()

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Compiler options
set(STM32_MCU_FLAGS  "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard " )

#Linker options
set(STM32_LINKER_SCRIPT stm32h747xx_flash_CM7.ld)
set(STM32_LINKER_OPTION  )

# Include toolchain file
include("../../../gcc-arm-none-eabi.cmake")

# Set the project name
set(CMAKE_PROJECT_NAME stm32-knight-touchgfx-burn-test-cm7)
project(${CMAKE_PROJECT_NAME})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Include mx-generated 
include("structure.cmake")

# In order to use CMake for cross-compiling
set(CMAKE_CXX_COMPILER_FORCED true)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()

# Fixed undefined reference to `_sbrk'
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nosys.specs")
