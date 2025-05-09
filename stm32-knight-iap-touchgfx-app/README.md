# stm32-knight-iap-touchgfx-app

VSCode debug breakpoint failed when code runtime error.

## SysTick

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        HAL_IncTick();
    }
}
```

## Debug

`.vscode/launch.json`

```json
"configurations":[
    {
        "name":"APP_0 Build & Debug Microcontroller - ST-Link",
        "cwd":"${workspaceFolder}",
        "type":"cortex-debug",
        "executable":"${workspaceFolder}/build/cm7/build/stm32-knight-iap-touchgfx-app-cm7.elf",
        "executable":"${command:cmake.launchTargetPath}",
        :"${command:cmake.launchTargetPath}":"${workspaceFolder}/path/to/filename.elf""postLaunchCommands":[
            "monitor halt",
            "set $sp = *(uint32_t*)0x08040000",
            "set $pc = *(uint32_t*)0x08040004",
            "set *(uint32_t*)0xE000ED08 = 0x08040000",
            "break main",
            "continue"
        ],
        "request":"launch",
        "servertype":"stlink",
        "device":"STM32H747XIHx",
        "interface":"swd",
        "serialNumber":"",
        "runToEntryPoint":"main",
        "svdFile":"${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H747_CM7.svd",
        "v1":false,
        "serverpath":"${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
        "stm32cubeprogrammer":"${config:STM32VSCodeExtension.cubeCLT.path}/STM32CubeProgrammer/bin",
        "stlinkPath":"${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
        "armToolchainPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin",
        "gdbPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",
        "serverArgs":[
            "-m",
            "0"
        ]
    },
    {
        "name":"APP_1 Build & Debug Microcontroller - ST-Link",
        "cwd":"${workspaceFolder}",
        "type":"cortex-debug",
        "executable":"${workspaceFolder}/build/cm7/build/stm32-knight-iap-touchgfx-app-cm7.elf",
        "executable":"${command:cmake.launchTargetPath}",
        :"${command:cmake.launchTargetPath}":"${workspaceFolder}/path/to/filename.elf""postLaunchCommands":[
            "monitor halt",
            "set $sp = *(uint32_t*)0x080A0000",
            "set $pc = *(uint32_t*)0x080A0004",
            "set *(uint32_t*)0xE000ED08 = 0x080A0000",
            "break main",
            "continue"
        ],
        "request":"launch",
        "servertype":"stlink",
        "device":"STM32H747XIHx",
        "interface":"swd",
        "serialNumber":"",
        "runToEntryPoint":"main",
        "svdFile":"${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H747_CM7.svd",
        "v1":false,
        "serverpath":"${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
        "stm32cubeprogrammer":"${config:STM32VSCodeExtension.cubeCLT.path}/STM32CubeProgrammer/bin",
        "stlinkPath":"${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
        "armToolchainPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin",
        "gdbPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",
        "serverArgs":[
            "-m",
            "0"
        ]
    },
]
```

`CMakeUserPresets.json`

```json
"configurePresets":[
    {
        "name":"local-debug-bootloader",
        "inherits":"debug",
        "cacheVariables":{
            "BUILD_TARGET":"STM32H747I_DISCO",
            "BUILD_CONTEXT":"CM7,BOOTLOADER,AUTO_JUMP_0"
        }
    },
    {
        "name":"local-debug-app-0",
        "inherits":"debug",
        "cacheVariables":{
            "BUILD_TARGET":"STM32H747I_DISCO",
            "BUILD_CONTEXT":"CM7,APP_0"
        }
    },
    {
        "name":"local-debug-app-1",
        "inherits":"debug",
        "cacheVariables":{
            "BUILD_TARGET":"STM32H747I_DISCO",
            "BUILD_CONTEXT":"CM7,APP_1"
        }
    }
]
```

## TouchGFX

Non TouchGFX Designer generated:

App/

target/

GUI.touchgfx
