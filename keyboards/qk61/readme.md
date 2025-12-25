# CIDOO QK61
A customizable 85key keyboard.

* Hardware Supported: CIDOO QK61 PCB with es32fs026 microcontroller

Compile firmware (after setting up your build environment):

    qmk compile -kb qk61 -mb default

Flash the firmware by connecting keyboard to your PC while holding ESC, then drop the firmware to the appeared drive

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## ATTENTION:
- Lightning control in VIA doesn't work
- You can't control the little light thingy left to esc button

If that's important for you, don't flash the firmware.

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB

## Notes
- Keyboard doesn't work without VIA (`VIA_ENABLE = yes` in `rules.mk`), probably because of the proprietary library. I am not sure if it affects any features tho, except wasting space.
- You can use VIA by importing "CIDOO QK61 VIA.JSON" in https://usevia.app/. Open settings, enable "Show design tab" and load draft definition in this new design tab
- [Upstreaming guide](https://docs.qmk.fm/newbs_git_using_your_master_branch)