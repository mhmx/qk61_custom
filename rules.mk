# Build Options
#   change yes to no to disable
#
# Board: it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards

BOARD = FS026
EEPROM_CUSTOM = custom
NO_USB_STARTUP_CHECK = yes
BLUETOOTH_CUSTOM = yes
DEBOUNCE_TYPE = asym_eager_defer_pk

# from keyboard/layout rules.mk
VIA_ENABLE = yes
EEPROM_DRIVER = custom

# custom lines for my firmware
TAP_DANCE_ENABLE = yes
DYNAMIC_KEYMAP_LAYER_COUNT = 5 # 5 layers, also add line to config.h

# to reduce firmware size
CONSOLE_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 

# if you renamed qk61.c->keyboard.c, add this path
SRC +=keyboard.c

# added combo support
COMBO_ENABLE = yes