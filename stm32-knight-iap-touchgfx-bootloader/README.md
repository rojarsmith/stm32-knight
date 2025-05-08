# stm32-knight-iap-touchgfx-bootloader

Paired with `stm32-knight-iap-touchgfx-app`.

Jump

Hold joy to right and click Wakeup button→Jump to APP_0

Hold joy to left and click Wakeup button→Jump to APP_1

## Troubleshooting

Failed to launch GDB: Error finishing flash operation (from target-download)

STM32_Programmer_CLI -c port=SWD mode=UR -halt

STM32_Programmer_CLI -c port=SWD mode=UR -e all -d build/cm7/build/stm32-knight-iap-touchgfx-bootloader-cm7.elf -rst

Hardware failures
