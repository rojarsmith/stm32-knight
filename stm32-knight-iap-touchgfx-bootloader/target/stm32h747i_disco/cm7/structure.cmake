message("[structure.cmake]")
set(ADDRESS_BOOTLOADER 0x08000000)
set(   SIZE_BOOTLOADER       128K)
set(   ADDRESS_FW_INFO 0x08020000)
set(      SIZE_FW_INFO       128K)
set(     ADDRESS_APP_0 0x08040000)
set(     ADDRESS_APP_1 0x080A0000)

message(STATUS "ADDRESS_BOOTLOADER: " ${ADDRESS_BOOTLOADER})
message(STATUS "SIZE_BOOTLOADER: " ${SIZE_BOOTLOADER})
message(STATUS "ADDRESS_FW_INFO: " ${ADDRESS_FW_INFO})
message(STATUS "SIZE_FW_INFO: " ${SIZE_FW_INFO})

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
    ../../../application/core0/src/syscalls.c
    ../../../target/common/system_stm32h7xx.c
    ../../../target/stm32h747i_disco/cm7/src/stm32h7xx_hal_msp.c
    ../../../target/stm32h747i_disco/cm7/src/stm32h7xx_it.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/adv7533/adv7533.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/adv7533/adv7533_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/is42s32800j/is42s32800j.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/nt35510/nt35510.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/nt35510/nt35510_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/otm8009a/otm8009a.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/Components/otm8009a/otm8009a_reg.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_bus.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_lcd.c
    ../../../../stm32-knight-sdk/firmware/Drivers/BSP/STM32H747I-DISCO/stm32h747i_discovery_sdram.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
	../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma2d.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dsi.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
	../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
	../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_ltdc.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c	
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
    ../../../../stm32-knight-sdk/firmware/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c
    ./startup_stm32h747xx_CM7.s
)

if(${BUILD_CONTEXT} MATCHES .*BOOTLOADER.*)
    message("   Target Source: BOOTLOADER")

    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ../../../application/core0/src/main_bootloader.c
    )
else()
    message(ERROR "BUILD_CONTEXT invalid.")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    ADDRESS_BOOTLOADER=${ADDRESS_BOOTLOADER}
    ADDRESS_FW_INFO=${ADDRESS_FW_INFO}
    ADDRESS_APP_0=${ADDRESS_APP_0}
    ADDRESS_APP_1=${ADDRESS_APP_1}
)
configure_file(stm32h747xx_flash_CM7.ld.in ${CMAKE_BINARY_DIR}/stm32h747xx_flash_CM7.ld @ONLY)
configure_file(stm32h747xx_flash_CM7.ld.in ${CMAKE_CURRENT_SOURCE_DIR}/stm32h747xx_flash_CM7.ld @ONLY)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} 
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
