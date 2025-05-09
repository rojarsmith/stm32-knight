# stm32-knight-iap-touchgfx-bootloader

Paired with `stm32-knight-iap-touchgfx-app`.

## Jump

Press and hold the right arrow key on the motherboard:

- Right key and click Wakeup button: Jump to APP_0

- Left key and click Wakeup button: Jump to APP_1

## Troubleshooting

**Failed to launch GDB: Error finishing flash operation (from target-download)**

Check:

- Change the USB port used by the PC to connect to the ST-Link. If you use a multi-layer USB HUB, try to change it to a USB port directly plugged into the computer host.

- STM32_Programmer_CLI -c port=SWD mode=UR -halt

- STM32_Programmer_CLI -c port=SWD mode=UR -e all -d build/cm7/build/stm32-knight-iap-touchgfx-bootloader-cm7.elf -rst

- Hardware failures
