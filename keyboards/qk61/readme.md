# CIDOO QK61

A customizable 61-key 60% wireless keyboard.

* Hardware Supported: CIDOO QK61 PCB with ES32 FS026 microcontroller
* Hardware Availability: CIDOO QK61

## Building

    qmk compile -kb qk61 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with the [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing

Connect the keyboard while holding Esc. A mass storage drive appears; copy the firmware file to it.

You can also press `QK_BOOT`, if your keymap has it, or the reset button on the back of the PCB.

## VIA

Keep `VIA_ENABLE = yes` in `rules.mk`. The board fails to initialize without it.

Build any keymap, then load `CIDOO QK61 VIA.JSON` in <https://usevia.app/> (enable **Show Design tab** first). VIA needs a USB connection — it does not work over 2.4 GHz or Bluetooth.

## Lighting

RGB Matrix drives 64 LEDs. The last three are the bar left of Esc, exposed to VIA under **logo**; the rest are under **Backlight**. Both have keycodes: `RM_*` and `LG_*`.

## Notes

* VIA offers both `UG_*` and `RM_*` keycodes because the definition declares `qmk_lighting` while the menus use both lighting channels. Only `RM_*` does anything.
* [Upstreaming guide](https://docs.qmk.fm/newbs_git_using_your_master_branch)
