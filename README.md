# STM32 Knight

## stm32-knight-iap

Modify `.vscode/launch.json`

```json
"executable": "${workspaceFolder}/build/cm7/build/stm32-knight-iap-cm7.elf",
// "executable": "${command:cmake.launchTargetPath}",
```

Rebuild:

Delete folder `build`→Modify `CMakeUserPresets.json`

```json
{
    "version": 3,
    "configurePresets": [
        {
            "name": "local-debug",
            "inherits": "debug",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "BUILD_TARGET": "STM32H747I_DISCO",
                // Type 1:
                "BUILD_CONTEXT": "CM7,BOOTLOADER",
                "BUILD_CONTEXT_S0": "CM7,APP_0"
            }
        }
    ]
}

// Type 2:
"BUILD_CONTEXT_S0": "CM7,BOOTLOADER",
"BUILD_CONTEXT": "CM7,APP_0"
// Type 3:
"BUILD_CONTEXT_S0": "CM7,BOOTLOADER",
"BUILD_CONTEXT": "CM7,APP_1"
```

→CMake→PROJECT OUTLINE Config All Projects

→stm32-knight-iap-cm7 Build→CMakeLists.txt Configure with CMake Debugger

## stm32-knight-ltdc

LTDC

## stm32-knight-template-minimal

Purpose:

Correctly set the MCU register to generate a delay of 10 seconds.

Feature:

- STM32CubeCLT
- CMake
- Multi-core
- Multi target board

STM32 VS Code Extension→Import CMake project→Board→Actions→Open in this window

Board:

- STM32F746G-DISCO
- STM32H747I-DISCO

Debug:

Project Outline→Configure with CMake Debugger→Select and Start Debug Configuration→Debug CM7 - ST-Link

Select Board:

Clean Project→Delete .vscode→Modfy CMakeUserPresets.json→STM32 VS Code Extension→Import CMake project

`CMakeUserPresets.json`

```json
{
    "version": 3,
    "configurePresets": [
        {
            "name": "local-debug",
            "inherits": "debug",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "BUILD_TARGET": "STM32H747I_DISCO",
                "BUILD_CONTEXT": "CM7"
            }
        }
    ]
}
```

```json
{
    "version": 3,
    "configurePresets": [
        {
            "name": "local-debug",
            "inherits": "default",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug",
                "BUILD_TARGET": "STM32F746G_DISCO"
            }
        }
    ],
    "buildPresets": [
        {
            "name": "local-debug",
            "configurePreset": "local-debug"
        }
    ]
}
```

Troubleshooting:

Q: Project Outline not correct.

A: Re-open the project.

Q: Can not close CMake Debugger in Call Stack.

A: Re-open the project or use `Reload Window` command at command panel.

Q: Debug STM32F746G-DISCO meet with `"executable": "${command:STM32VSCodeExtension.dualCoreTarget}"` not define.

A: Use new path `"executable": "${workspaceFolder}/build/stm32-knight-template-minimal-target.elf"` then ignore all wrong.

Q: Not find `Debug CM7 - ST-Link` ?

A: Import CMake project again.

Q: Not found binary ?

A: `.vscode/launch.json` modify:

```json
"configurations": [{
    "executable": "${workspaceFolder}/build/core0/build/stm32-knight-xxx-core0.elf",
}]
```

## utility

### freertos-win-example

`.vscode/launch.json`

```json
{
    "version": "0.2.0",
    "configurations": [{
        "name": "Debug FreeRTOS Windows Simulation",
        "type": "cppvsdbg",
        "request": "launch",
        "program":"C:/my/Build/GitPublic/stm32-knight/stm32-knight-sdk/utility/freertos-win-example/out/build/local-debug/src/Debug/freertos-win-example.exe",
        // "program": "${workspaceFolder}/out/build/local-debug/src/Debug/freertos-win-example.exe",
        "args": [],
        "cwd": "${workspaceFolder}",
        "environment": [],
        "console": "externalTerminal",
        // for "type": "cppdbg",
        // "setupCommands": [
        //     { "description": "Enable non-stop mode", "text": "set non-stop on", "ignoreFailures": true },
        //     { "description": "Enable scheduler locking", "text": "set scheduler-locking on", "ignoreFailures": true }
        // ]
    }],

}
```

In debug mode and freezon at:

xWinApiResult = WaitForMultipleObjects( sizeof( pvObjectList ) / sizeof( void * ), pvObjectList, TRUE, xTimeoutMilliseconds );

Need correct `setupCommands` for `cppdbg`.
