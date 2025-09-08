/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define less important options */

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
#define FORCE_NKRO
/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
 */

#define MATRIX_UNSELECT_DRIVE_HIGH
#define CORTEX_ENABLE_WFI_IDLE          FALSE

/* Ensure we jump to bootloader if the RESET keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define DEBOUNCE 5

#ifndef NOP_FUDGE
#define NOP_FUDGE 0.4
#endif

#define RGB_MATRIX_LED_COUNT 64
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_SLEEP

// lines from config.h at /keymaps folder
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  1151
#define EEPROM_SIZE 1152

#define FEE_PAGE_SIZE (0x200)
#define FEE_PAGE_COUNT (8)

#define FEE_PAGE_BASE_ADDRESS (0x1F000)
#define FEE_MCU_FLASH_SIZE (0x1000)

#define EECONFIG_USER_DATA_SIZE 4

#define EECONFIG_KB_DATA_SIZE 1

#define TRANSIENT_EEPROM_SIZE 4096

// custom lines
#define DYNAMIC_KEYMAP_LAYER_COUNT 5 // 5 layers, also add to rules.mk
#define TAPPING_TERM 150	         // custom delay for Tap Dance (default 200 ms)
#define COMBO_TERM 25                // 50 ms - default delay for Combos

