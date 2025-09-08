# CIDOO QK61 custom firmware

A customizable 61key keyboard.

__Advanced Tap Dance and LT support__

* Keyboard Maintainer: [CIDOO](https://github.com/CIDOOKeyboard)
* Hardware Supported: CIDOO QK61 PCB with es32fs026 microcontroller

Make example for this keyboard (after setting up your build environment):

    make qk61:custom

Flashing example for this keyboard:

    make qk61:custom:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
