/* Copyright 2025 CIDOO
 * Copyright 2025 CIDOO <https://github.com/CIDOOKeyboard>
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

#include "../../lib/rdr_lib/rdr_common.h"

void matrix_io_delay(void) {
}

void matrix_output_select_delay(void) {
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
}

led_config_t g_led_config = { {
    { 0        , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED   , NO_LED    },
	{ NO_LED   , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       , 12       , 13       , NO_LED   , NO_LED    },
	{ 14       , 15       , 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       , 24       , 25       , 26       , 27       , NO_LED   , NO_LED    },
	{ 28       , 29       , 30       , 31       , 32       , 33       , 34       , 35       , 36       , 37       , 38       , 39       , NO_LED   , 40       , NO_LED   , NO_LED    },
	{ 41       , NO_LED   , 42       , 43       , 44       , 45       , 46       , 47       , 48       , 49       , 50       , 51       , NO_LED   , 52       , NO_LED   , NO_LED    },
	{ 53       , 54       , 55       , NO_LED   , NO_LED   , 56       , NO_LED   , NO_LED   , NO_LED   , 57       , 58       , 59       , 60       , NO_LED   , NO_LED   , NO_LED    }
},{
    { 0 , 10},  { 16, 10},  { 32, 10},  { 48, 10},  { 64, 10},   { 80, 10},  { 96,  10}, { 112, 10}, { 128, 10}, { 144, 10}, { 160, 10}, { 176, 10}, { 192, 10}, { 220, 10},
    { 4 , 20},  { 24, 20},  { 40, 20},  { 56, 20},  { 72, 20},   { 88, 20},  { 104, 20}, { 120, 20}, { 136, 20}, { 152, 20}, { 168, 20}, { 184, 20}, { 200, 20}, { 222, 20},
    { 4 , 30},  { 28, 30},  { 44, 30},  { 60, 30},  { 76, 30},   { 92, 30},  { 108, 30}, { 124, 30}, { 140, 30}, { 156, 30}, { 172, 30}, { 188, 30},             { 216, 30},
    { 8 , 40},              { 35, 40},  { 51, 40},  { 67, 40},   { 83, 40},  { 99 , 40}, { 115, 40}, { 131, 40}, { 147, 40}, { 163, 40}, { 180, 40},             { 224, 40},
    { 0 , 50},  { 20, 50},  { 40, 50},                           { 110,50},                                                  { 176, 50}, { 192, 50}, { 208, 40}, { 224, 40},

    { 225, 65}, { 225, 65}, {225, 65}
}, {
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,      1,  1,  1,  1,  1,  1,  1,  1,  1,  1,      1,
    1,  1,  1,          1,                  1,  1,  1,  1,

    0,  0,  0
} };

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    User_Led_Show();
    return false;
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state)  {
    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        if(usb_device_state == USB_DEVICE_STATE_CONFIGURED) {
            Usb_If_Ok = true;//usb枚举完成
            Usb_If_Ok_Led = true;
            Usb_If_Ok_Delay = 0;
        } else {
            Usb_If_Ok = false;
		    Usb_If_Ok_Led = false;
        }
    } else {
        Usb_If_Ok = false;
	    Usb_If_Ok_Led = false;
    }
}

void housekeeping_task_user(void) {
    User_Keyboard_Reset();
    es_chibios_user_idle_loop_hook();
}

void board_init(void) {
    User_Keyboard_Init();
}

void keyboard_post_init_user(void) {
    User_Keyboard_Post_Init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {   /*键盘只要有按键按下就会调用此函数*/
    Usb_Change_Mode_Delay = 0;                                      /*只要有按键就不会进入休眠*/
    Usb_Change_Mode_Wakeup = false;

    return Key_Value_Dispose(keycode, record);
}
