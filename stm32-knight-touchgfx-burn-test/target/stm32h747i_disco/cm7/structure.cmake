set(ADDRESS_BOOTLOADER 0x08000000)
set(ADDRESS_APP_0 0x08000000)
set(ADDRESS_APP_1 0x080A0000)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE 
	CORE_CM7 
	USE_HAL_DRIVER 
	STM32H747xx 
	USE_PWR_DIRECT_SMPS_SUPPLY
    __SOFT_FP__
    $<$<CONFIG:Debug>:DEBUG>
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ../../../application/core0/inc
    ../../../target/stm32h747i_disco/cm7/inc
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/adv7533
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/Common
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/is42s32800j
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/mt25tl01g
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/nt35510
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/otm8009a
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO
    ../../../../stm32-knight-sdk/firmware/Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ../../../../stm32-knight-sdk/firmware/Drivers/CMSIS/Include
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Inc
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ../../../application/core0/src/freertos.c
    ../../../application/core0/src/syscalls.c
    ../../../target/common/system_stm32h7xx.c
    ../../../target/stm32h747i_disco/cm7/src/stm32h7xx_hal_msp.c
    ../../../target/stm32h747i_disco/cm7/src/stm32h7xx_hal_timebase_tim.c
    ../../../target/stm32h747i_disco/cm7/src/stm32h7xx_it.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/adv7533/adv7533.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/adv7533/adv7533_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/ft6x06/ft6x06.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/ft6x06/ft6x06_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/is42s32800j/is42s32800j.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/mt25tl01g/mt25tl01g.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/nt35510/nt35510.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/nt35510/nt35510_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/otm8009a/otm8009a.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/otm8009a/otm8009a_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_qspi.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_ts.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
	../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_crc_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dsi.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
	../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_jpeg.c
	../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c	
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c
    ./startup_stm32h747xx_CM7.s
)

if(${BUILD_CONTEXT} MATCHES .*APP_0.*)
    message("   Goal: APP_0")
    
    set(FLASH_ORIGIN ${ADDRESS_APP_0} CACHE STRING "Start address of the Flash memory" FORCE)
    set(FLASH_LENGTH 1024K CACHE STRING "Length of the Flash memory" FORCE)
    
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        GOAL_APP
    )

    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ../../../gui/TouchGFX/App
        ../../../gui/TouchGFX/generated/fonts/include
        ../../../gui/TouchGFX/generated/gui_generated/include
        ../../../gui/TouchGFX/generated/images/include
        ../../../gui/TouchGFX/generated/images/include/images/include
        ../../../gui/TouchGFX/generated/texts/include
        ../../../gui/TouchGFX/generated/videos/include
        ../../../gui/TouchGFX/gui/include
        ../../../gui/TouchGFX/target
        ../../../gui/TouchGFX/target/generated
        ${CMSIS_RTOS_V2}
        ${FREERTOS_KERNEL_PATH}/include
        ${FREERTOS_KERNEL_PATH}/portable/GCC/ARM_CM7/r0p1
        ${TOUCHGFX_PATH}/touchgfx/3rdparty/libjpeg/include
        ${TOUCHGFX_PATH}/touchgfx/framework/include
    )

    file(GLOB_RECURSE CPP_SRC_TGFX_GEN 
        ../../../gui/TouchGFX/generated/**/*.cpp
        ../../../gui/TouchGFX/generated/**/**/*.cpp
        ../../../gui/TouchGFX/generated/fonts/src/*.cpp
        ../../../gui/TouchGFX/generated/images/src/*.cpp
        ../../../gui/TouchGFX/generated/images/src/**/*.cpp
        ../../../gui/TouchGFX/gui/**/*.cpp
        ../../../gui/TouchGFX/gui/**/**/*.cpp
        ../../../gui/TouchGFX/gui/**/widget/*.cpp
    )
    list(FILTER CPP_SRC_TGFX_GEN EXCLUDE REGEX ".*\/simulator\/.*")
    file(GLOB_RECURSE CPP_SRC_TGFX_TAR
        ../../../gui/TouchGFX/target/*.cpp
        ../../../gui/TouchGFX/target/**/*.cpp
    )
    list(FILTER CPP_SRC_TGFX_TAR EXCLUDE REGEX ".*\/simulator\/.*")
    message(STATUS "CPP_SRC_TGFX_TAR: ${CPP_SRC_TGFX_TAR}")

    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ../../../application/core0/src/main_app.c
        ../../../gui/TouchGFX/App/app_touchgfx.c
        ${CPP_SRC_TGFX_GEN}
        ${CPP_SRC_TGFX_TAR}
        ${CMSIS_RTOS_V2}/cmsis_os2.c
        ${FREERTOS_KERNEL_PATH}/portable/GCC/ARM_CM7/r0p1/port.c
        ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
        ${FREERTOS_KERNEL_PATH}/event_groups.c
        ${FREERTOS_KERNEL_PATH}/list.c
        ${FREERTOS_KERNEL_PATH}/queue.c
        ${FREERTOS_KERNEL_PATH}/tasks.c
        ${FREERTOS_KERNEL_PATH}/timers.c
    )

    set(LIB_TGFX 
        ${TOUCHGFX_PATH}/touchgfx/lib/core/cortex_m7/gcc
    )

    message(STATUS "LIB_TGFX: ${LIB_TGFX}")
elseif(${BUILD_CONTEXT} MATCHES .*APP_1.*)
    message("   Goal: APP_1")
    
    set(FLASH_ORIGIN ${ADDRESS_APP_1} CACHE STRING "Start address of the Flash memory" FORCE)
    set(FLASH_LENGTH "384K" CACHE STRING "Length of the Flash memory" FORCE)
    
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        GOAL_APP
    )

    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ../../../application/core0/src/main_app.c
    )
endif()

message(STATUS "FLASH_ORIGIN: " ${FLASH_ORIGIN})
message(STATUS "FLASH_LENGTH: " ${FLASH_LENGTH})

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    FLASH_ORIGIN=${FLASH_ORIGIN}
    ADDRESS_BOOTLOADER=${ADDRESS_BOOTLOADER}
    ADDRESS_APP_0=${ADDRESS_APP_0}
    ADDRESS_APP_1=${ADDRESS_APP_1}
    USE_BPP=24
)
configure_file(stm32h747xx_flash_CM7.ld.in ${CMAKE_BINARY_DIR}/stm32h747xx_flash_CM7.ld @ONLY)
configure_file(stm32h747xx_flash_CM7.ld.in ${CMAKE_CURRENT_SOURCE_DIR}/stm32h747xx_flash_CM7.ld @ONLY)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} 
)

if(${BUILD_CONTEXT} MATCHES .*APP_0.*)
    add_library(touchgfx STATIC IMPORTED)
    set_target_properties(touchgfx PROPERTIES IMPORTED_LOCATION ${LIB_TGFX}/libtouchgfx-float-abi-hard.a)
    target_link_libraries(${PROJECT_NAME} touchgfx)
endif()

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
