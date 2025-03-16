# STM32 Knight

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

