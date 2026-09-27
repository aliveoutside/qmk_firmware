# Build Options
#   change yes to no to disable
#
# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
BOARD = 				FS026
EEPROM_DRIVER =			custom
NO_USB_STARTUP_CHECK = 	yes
BLUETOOTH_CUSTOM = 		yes

DEBOUNCE_TYPE = 		custom
RAW_ENABLE            = yes   # provides raw_hid_send()
DYNAMIC_KEYMAP_ENABLE = yes   # explicit for clarity, VIA sets it implicitly
VIA_ENABLE = 			yes

# Include common library (replaces rdr_lib)
VPATH += keyboards/qk61/common
SRC += rdmctmzt_common.c
SRC += quantum/dynamic_keymap.c
SRC += three_mode.c
SRC += user_battery.c
SRC += user_debounce.c
SRC += user_eeprom.c
SRC += user_emi.c
SRC += user_led_custom.c
SRC += user_logo_custom.c
SRC += user_spi.c
SRC += user_system.c

VPATH += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md
SRC += lib/chibios-contrib/os/common/ext/CMSIS/ES32/FS026/md/md_spi.c