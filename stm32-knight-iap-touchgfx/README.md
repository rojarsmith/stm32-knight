# stm32-knight-iap-touchgfx

```json
        {
            "name": "APP_0 Build & Debug Microcontroller - ST-Link",
            "cwd": "${workspaceFolder}",
            "type": "cortex-debug",
            "executable": "${workspaceFolder}/build/cm7/build/stm32-knight-iap-touchgfx-cm7.elf",
            // "executable": "${command:cmake.launchTargetPath}",
            // Let CMake extension decide executable: "${command:cmake.launchTargetPath}"
            // Or fixed file path: "${workspaceFolder}/path/to/filename.elf"
            "postLaunchCommands": [
                "monitor halt",
                "set $sp = *(uint32_t*)0x08040000",
                "set $pc = *(uint32_t*)0x08040004",
                "set *(uint32_t*)0xE000ED08 = 0x08040000",  // SCB->VTOR
                "break main",
                "continue"
              ],
            "request": "launch",
            "servertype": "stlink",
            "device": "STM32H747XIHx", //MCU used
            "interface": "swd",
            "serialNumber": "",        //Set ST-Link ID if you use multiple at the same time
            "runToEntryPoint": "main",
            "svdFile": "${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32H747_CM7.svd",
            "v1": false,               //Change it depending on ST Link version
            "serverpath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",
            "stm32cubeprogrammer":"${config:STM32VSCodeExtension.cubeCLT.path}/STM32CubeProgrammer/bin",
            "stlinkPath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",   
            "armToolchainPath": "${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin",
            "gdbPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",            
            "serverArgs": [
                "-m","0",
            ]
        },
```

