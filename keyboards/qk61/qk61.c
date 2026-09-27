/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/Linger7857>
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

#include "common/rdmctmzt_common.h"

bool Key_Fn_Status = false;
bool User_Key_Batt_Num_Show = false;
uint8_t User_Key_Batt_Count = 0;
uint8_t Led_Point_Count = 0U;
uint8_t Mac_Win_Point_Count = 0U;
bool Test_Led = false;
uint8_t Test_Colour = 0U;

// QK61-specific LED indices
#define LED_CAP_INDEX       (28)
#define LED_WIN_L_INDEX     (54)
#define LED_BATT_INDEX      (1)

// QK61 mode indicator LED indices - using keys that should be visible
#define LED_BLE_1_INDEX     (15)  // 'Q' key position
#define LED_BLE_2_INDEX     (16)  // 'W' key position
#define LED_BLE_3_INDEX     (17)  // 'E' key position
#define LED_2P4G_INDEX      (18)  // 'R' key position
#define LED_USB_INDEX       (19)  // 'T' key position

// QK61 battery level indicator mapping
uint8_t Led_Batt_Index_Tab[10] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
};

// Local Caps Lock state tracking for wireless modes
static bool local_caps_lock_state = false;

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

void notify_usb_device_state_change_user(struct usb_device_state usb_device_state)  {
    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        switch (usb_device_state.configure_state) {
            case USB_DEVICE_STATE_CONFIGURED:
                Usb_If_Ok_Led = true;
                break;
            case USB_DEVICE_STATE_SUSPEND:
                // Handle suspend state - keyboard is in low power mode
                Usb_If_Ok_Led = false;
                break;
            case USB_DEVICE_STATE_INIT:
            case USB_DEVICE_STATE_NO_INIT:
            default:
                Usb_If_Ok_Led = false;
                break;
        }
    } else {
        Usb_If_Ok_Led = false;
    }
}

void housekeeping_task_user(void) {
    es_chibios_user_idle_loop_hook();
}

void board_init(void) {
    es_ble_spi_init();          // SPI initialization
    User_Adc_Init();            // ADC initialization
    eeprom_driver_init();       // EEPROM initialization
    rgb_matrix_driver_init();   // PWM DMA initialization
    Init_Gpio_Infomation();     // GPIO initialization
    Init_Keyboard_Infomation(); // Keyboard info initialization
    Init_Batt_Infomation();     // Battery info initialization
    User_Systime_Init();        // System timer initialization

    if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
        User_Usb_Init();
        Led_Rf_Pair_Flg = false;
    } else {
        Usb_Disconnect();
    }

    Init_Spi_Power_Up = true;
    Init_Spi_100ms_Delay = 0;
    Spi_Interval = SPI_DELAY_RF_TIME;
    NVIC_SetPriority(PendSV_IRQn, 3);
    NVIC_SetPriority(SysTick_IRQn, 3);

    Usb_If_Ok_Led = false;
    Led_Power_Up = true;
    Emi_Test_Start = false;
    Keyboard_Reset = false;
}

void keyboard_post_init_kb(void) {
    // NKRO is unreliable over Bluetooth, only honour the saved setting on USB and 2.4G
    if (Keyboard_Info.Key_Mode != QMK_BLE_MODE && keymap_config.nkro != Keyboard_Info.Nkro) {
        keymap_config.nkro = Keyboard_Info.Nkro;
    }

    if (Keyboard_Info.Mac_Win_Mode) {
        uint8_t current_layer = get_highest_layer(layer_state);
        if (current_layer != 1) {
            layer_on(1);
        }
    }
    keyboard_post_init_user();
}

// LED display functions adapted from womier common
void Led_Rf_Mode_Show(void) {
    uint8_t Temp_Colour = 0, Led_Index = 0;
    if (Keyboard_Info.Key_Mode == QMK_BLE_MODE) {
        if (Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_1) {
            Temp_Colour = 5;
            Led_Index = LED_BLE_1_INDEX;
        } else if (Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_2) {
            Temp_Colour = 5;
            Led_Index = LED_BLE_2_INDEX;
        } else if (Keyboard_Info.Ble_Channel == QMK_BLE_CHANNEL_3) {
            Temp_Colour = 5;
            Led_Index = LED_BLE_3_INDEX;
        }
    } else if (Keyboard_Info.Key_Mode == QMK_2P4G_MODE) {
        Temp_Colour = 3;
        Led_Index = LED_2P4G_INDEX;
    }

    if (Keyboard_Status.System_Connect_Status == KB_MODE_CONNECT_PAIR) {
        if (Systick_Led_Count < 10) {
            rgb_matrix_set_color(Led_Index, Led_Colour_Tab[Temp_Colour][0], Led_Colour_Tab[Temp_Colour][1], Led_Colour_Tab[Temp_Colour][2]);
        } else {
            rgb_matrix_set_color(Led_Index, 0, 0, 0);
        }

        if (Systick_Led_Count >= 20) {
            Systick_Led_Count = 0;
        }
    } else if (Keyboard_Status.System_Connect_Status == KB_MODE_CONNECT_RETURN) {
        if (Systick_Led_Count < 25) {
            rgb_matrix_set_color(Led_Index, Led_Colour_Tab[Temp_Colour][0], Led_Colour_Tab[Temp_Colour][1], Led_Colour_Tab[Temp_Colour][2]);
        } else {
            rgb_matrix_set_color(Led_Index, 0, 0, 0);
        }

        if (Systick_Led_Count >= 50) {
            Systick_Led_Count = 0;
        }
    } else {
        rgb_matrix_set_color(Led_Index, Led_Colour_Tab[Temp_Colour][0], Led_Colour_Tab[Temp_Colour][1], Led_Colour_Tab[Temp_Colour][2]);

        if (Systick_Led_Count >= 240) {
            Systick_Led_Count = 0;
            Led_Rf_Pair_Flg = false;
            if (Keyboard_Info.Key_Mode == QMK_BLE_MODE) {
                User_Batt_Send_Spi = true;
            }
        }
    }
}

void Led_Power_Low_Show(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    if (Systick_Led_Count < 25) {
        rgb_matrix_set_color(LED_BATT_INDEX, U_PWM, 0x00, 0x00);
    } else {
        rgb_matrix_set_color(LED_BATT_INDEX, 0x00, 0x00, 0x00);
    }

    if (Systick_Led_Count >= 50) {
        Systick_Led_Count = 0;
    }
}

void Led_Point_Flash_Show(void) {
    if (Systick_Led_Count < 25) {
        if (Led_Point_Count) {
            // Regular LED point counting - light all LEDs
            rgb_matrix_driver_set_color_all(U_PWM, U_PWM, U_PWM);
        } else if (Mac_Win_Point_Count) {
            // Mac/Win mode switching - only blink caps lock LED
            rgb_matrix_set_color(LED_CAP_INDEX, U_PWM, U_PWM, 0X00);
        }
    } else {
        if (Led_Point_Count) {
            // Turn off all LEDs for regular point counting
            rgb_matrix_driver_set_color_all(0X00, 0X00, 0X00);
        } else if (Mac_Win_Point_Count) {
            // Turn off only caps lock LED for Mac/Win mode switching
            rgb_matrix_set_color(LED_CAP_INDEX, 0X00, 0X00, 0X00);
        }
    }

    if (Systick_Led_Count >= 50) {
        Systick_Led_Count = 0;

        if (Led_Point_Count) {
            Led_Point_Count--;
        } else if (Mac_Win_Point_Count) {
            Mac_Win_Point_Count--;
        }
    }
}

void Led_Batt_Number_Show(void) {
    if (es_stdby_pin_state == 1) {
        if (Batt_Led_Count >= 2) {
            Batt_Led_Count = 0;

            if (User_Key_Batt_Count > 3) {
                User_Key_Batt_Count -= 3;
            } else {
                User_Key_Batt_Count = 127;
            }
        }

        uint8_t Tmep_Pwm = User_Key_Batt_Count;

        for (uint8_t i = 0; i < 10; i++) {
            rgb_matrix_set_color(Led_Batt_Index_Tab[i], 0X00, Led_Wave_Pwm_Tab[Tmep_Pwm], 0X00);
            Tmep_Pwm += 8;
            if (Tmep_Pwm >= 128) {
                Tmep_Pwm -= 128;
            }
        }
    } else if (es_stdby_pin_state == 2) {
        for (uint8_t i = 0; i < 10; i++) {
            rgb_matrix_set_color(Led_Batt_Index_Tab[i], 0X00, 0XFF, 0X00);
        }
    } else {
        uint8_t Colour_R = 0, Colour_G = 0, Colour_B = 0;
        uint8_t Temp_Count = (Keyboard_Info.Batt_Number * 10) / 100;  // Scale to 10 LEDs
        if (Temp_Count > 10) {
            Temp_Count = 10;
        }

        if (Keyboard_Info.Batt_Number <= 20) {
            Colour_R = 0XFF;    Colour_G = 0X00;    Colour_B = 0X00;  // Red below 20%
        } else if (Keyboard_Info.Batt_Number <= 50) {
            Colour_R = 0XFF;    Colour_G = 0XFF;    Colour_B = 0X00;  // Yellow 20-50%
        } else {
            Colour_R = 0X00;    Colour_G = 0XFF;    Colour_B = 0X00;  // Green above 50%
        }

        for (uint8_t i = 0; i < Temp_Count; i++) {
            rgb_matrix_set_color(Led_Batt_Index_Tab[i], Colour_R, Colour_G, Colour_B);
        }
    }
}

void User_Point_Show(void){
    if (Led_Point_Count || Mac_Win_Point_Count) {
        Led_Point_Flash_Show();
    } else {
        Systick_Led_Count = 0;

        // Caps Lock indicator - use local state for all modes to ensure consistency
        if (Keyboard_Info.Key_Mode == QMK_USB_MODE) {
            // For USB mode, use the standard QMK LED state
            if (host_keyboard_led_state().caps_lock && Usb_If_Ok_Led) {
                rgb_matrix_set_color(LED_CAP_INDEX, U_PWM, U_PWM, U_PWM);
            } else {
                rgb_matrix_set_color(LED_CAP_INDEX, 0, 0, 0);  // Turn off the LED
            }
        } else {
            // For wireless modes, use our local tracking which should be more reliable
            if (local_caps_lock_state) {
                rgb_matrix_set_color(LED_CAP_INDEX, U_PWM, U_PWM, U_PWM);
            } else {
                rgb_matrix_set_color(LED_CAP_INDEX, 0, 0, 0);  // Turn off the LED
            }
        }

        if (Keyboard_Info.Win_Lock) {
            rgb_matrix_set_color(LED_WIN_L_INDEX, U_PWM, U_PWM, U_PWM);
        }
    }
}

void User_Test_Colour_Show(void){
    uint8_t Test_R = 0, Test_G = 0, Test_B = 0;
    switch(Test_Colour) {
        case 0:  Test_R = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_G = 0;                             Test_B = 0;                             break;
        case 1:  Test_R = 0;                             Test_G = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_B = 0;                             break;
        case 2:  Test_R = 0;                             Test_G = 0;                             Test_B = RGB_MATRIX_MAXIMUM_BRIGHTNESS; break;
        case 3:  Test_R = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_G = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_B = RGB_MATRIX_MAXIMUM_BRIGHTNESS; break;
        default: Test_R = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_G = RGB_MATRIX_MAXIMUM_BRIGHTNESS; Test_B = RGB_MATRIX_MAXIMUM_BRIGHTNESS; break;
    }
    rgb_matrix_driver_set_color_all(Test_R, Test_G, Test_B);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (User_Power_Low) {
        Led_Power_Low_Show();
    } else if (Test_Led) {
        User_Test_Colour_Show();
    } else if (Led_Rf_Pair_Flg && (Keyboard_Info.Key_Mode != QMK_USB_MODE)) {
        Led_Rf_Mode_Show();
    } else if (User_Key_Batt_Num_Show) {
        Led_Batt_Number_Show();
    } else {
        User_Point_Show();

        if (Key_Fn_Status) {
            switch (Keyboard_Info.Key_Mode) {
                case QMK_BLE_MODE: {
                    switch (Keyboard_Info.Ble_Channel) {
                        case QMK_BLE_CHANNEL_1: rgb_matrix_set_color(LED_BLE_1_INDEX, U_PWM, U_PWM, U_PWM); break;
                        case QMK_BLE_CHANNEL_2: rgb_matrix_set_color(LED_BLE_2_INDEX, U_PWM, U_PWM, U_PWM); break;
                        case QMK_BLE_CHANNEL_3: rgb_matrix_set_color(LED_BLE_3_INDEX, U_PWM, U_PWM, U_PWM); break;
                        default:                                                                            break;
                    } 
                } break;
                case QMK_2P4G_MODE:             rgb_matrix_set_color(LED_2P4G_INDEX, U_PWM, U_PWM, U_PWM);  break;
                case QMK_USB_MODE:              rgb_matrix_set_color(LED_USB_INDEX,  U_PWM, U_PWM, U_PWM);  break;
                default:                                                                                    break;
            }
        }
    }

    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    Usb_Change_Mode_Delay = 0;
    Usb_Change_Mode_Wakeup = false;

    if (Test_Led) {
        if ((keycode != KC_SPC) && (keycode != MO(2)) && (keycode != MO(3)) && (keycode != KC_LCTL)) {
            Test_Led = false;
        }
    }

    switch (keycode) {
        case QMK_KB_MODE_2P4G: {                                    //2.4G
            if (record->event.pressed) {
                Key_2p4g_Status = true;
                Usb_Disconnect();
                if (Keyboard_Info.Key_Mode != QMK_2P4G_MODE) {
                    Keyboard_Info.Key_Mode = QMK_2P4G_MODE;
                    Spi_Send_Commad(USER_SWITCH_2P4G_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                    // Show mode indicator for 1 second
                    Show_Mode_Indicator = true;
                    Mode_Indicator_Timer = timer_read();
                }
            } else {
                Key_2p4g_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE1: {
            if (record->event.pressed) {
                Key_Ble_1_Status = true;
                Usb_Disconnect();
                if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) || ((Keyboard_Info.Key_Mode == QMK_BLE_MODE) && (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_1))) {   /*如果当前模式不是BLE模式则切换为BLE，或者BLE通道不相同*/
                    Keyboard_Info.Key_Mode = QMK_BLE_MODE;
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_1;
                    Spi_Send_Commad(USER_SWITCH_BLE_1_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                    // Show mode indicator for 1 second
                    Show_Mode_Indicator = true;
                    Mode_Indicator_Timer = timer_read();
                }
            } else {
                Key_Ble_1_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE2: {
            if (record->event.pressed) {
                Key_Ble_2_Status = true;
                Usb_Disconnect();
                if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) || ((Keyboard_Info.Key_Mode == QMK_BLE_MODE) && (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_2))) {   /*如果当前模式不是BLE模式则切换为BLE，或者BLE通道不相同*/
                    Keyboard_Info.Key_Mode = QMK_BLE_MODE;
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_2;
                    Spi_Send_Commad(USER_SWITCH_BLE_2_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                    // Show mode indicator for 1 second
                    Show_Mode_Indicator = true;
                    Mode_Indicator_Timer = timer_read();
                }
            } else {
                Key_Ble_2_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_BLE3: {
            if (record->event.pressed) {
                Key_Ble_3_Status = true;
                Usb_Disconnect();
                if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) || ((Keyboard_Info.Key_Mode == QMK_BLE_MODE) && (Keyboard_Info.Ble_Channel != QMK_BLE_CHANNEL_3))) {   /*如果当前模式不是BLE模式则切换为BLE，或者BLE通道不相同*/
                    Keyboard_Info.Key_Mode = QMK_BLE_MODE;
                    Keyboard_Info.Ble_Channel = QMK_BLE_CHANNEL_3;
                    Spi_Send_Commad(USER_SWITCH_BLE_3_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                    // Show mode indicator for 1 second
                    Show_Mode_Indicator = true;
                    Mode_Indicator_Timer = timer_read();
                }
            } else {
                Key_Ble_3_Status = false;
            }
            Time_3s_Count = 0;
        } return true;
        case QMK_KB_MODE_USB: {
            if (record->event.pressed) {
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    Keyboard_Info.Key_Mode = QMK_USB_MODE;
                    Spi_Send_Commad(USER_SWITCH_USB_MODE);
                    es_restart_usb_driver();
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = false;
                    // Show mode indicator for 1 second
                    Show_Mode_Indicator = true;
                    Mode_Indicator_Timer = timer_read();
                }
            }
        } return true;
        case QMK_BATT_NUM: {
            if (record->event.pressed) {
                User_Key_Batt_Num_Show = true;
                User_Key_Batt_Count = 0;
            } else {
                User_Key_Batt_Num_Show = false;
                User_Key_Batt_Count = 0;
            }
        } return true;
        case QMK_WIN_LOCK: {
            if (!record->event.pressed) {
                if (Keyboard_Info.Mac_Win_Mode == INIT_MAC_MODE) {
                    if (Keyboard_Info.Win_Lock == INIT_WIN_LOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                        Save_Flash_Set();
                    }
                } else {
                    if (Keyboard_Info.Win_Lock == INIT_WIN_NLOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_LOCK;
                        unregister_code(KC_LGUI); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    } else {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    }
                    Save_Flash_Set();
                }
            }
        } return true;
        case QMK_KB_SIX_N_CH: {
            if (record->event.pressed) {
                if(keymap_config.nkro) {
                    es_change_qmk_nkro_mode_disable();
                    Mac_Win_Point_Count = 3;
                } else {
                    es_change_qmk_nkro_mode_enable();
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case QMK_TEST_COLOUR: {
            if (!record->event.pressed) {
                if (Test_Led == false) {
                    Test_Led = true;
                    Test_Colour = 0;
                }
            }
        } return true;
        case KC_SPC: {
            if (!record->event.pressed) {
                if (Test_Led) {
                    Test_Colour++;
                    if (Test_Colour >= 4) {
                        Test_Colour = 0;
                    }
                }
            }
        } return true;
        case KC_LGUI: {                                             //key_win_l
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case KC_RGUI: {                                             //key_win_r
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case KC_APP: {                                              //key_app
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
        } return true;
        case RM_VALU: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() >= RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RM_VALD: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() <= 0) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RM_SPDU: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() >= 255) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case RM_SPDD: {
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() <= 0) {
                    Led_Point_Count = 3;
                }
            }
        } return true;
        case MO(2): {                                               //FN
            if (record->event.pressed) {
                Key_Fn_Status = true;
            } else {
                Key_Fn_Status = false;
            }
        } return true;
        case MO(3): {                                               //FN
            if (record->event.pressed) {
                Key_Fn_Status = true;
            } else {
                Key_Fn_Status = false;
            }
        } return true;
        case TO(0): {                                               //WIN
            if (!record->event.pressed) {
                if ((record->event.key.col == WIN_COL) && (record->event.key.row == WIN_ROL) && (Keyboard_Info.Mac_Win_Mode != INIT_WIN_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
                    Mac_Win_Point_Count = 1;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        case TO(1): {                                               //MAC
            if (!record->event.pressed) {
                if ((record->event.key.col == MAC_COL) && (record->event.key.row == MAC_ROL) && (Keyboard_Info.Mac_Win_Mode != INIT_MAC_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_MAC_MODE;
                    Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    Mac_Win_Point_Count = 3;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        case EE_CLR: {
            if (record->event.pressed) {
                Key_Reset_Status = true;
                record->event.pressed = false;
            } else {
                Key_Reset_Status = false;
            }
            Func_Time_3s_Count = 0;
        } return true;
        case QMK_DEBUG_SWITCH: {
            if (record->event.pressed) {
                Debug_Mode_Switch_Position();
            }
        } return true;
        case QMK_MAC_WIN_CH: {
            if (!record->event.pressed) {
                if (Keyboard_Info.Mac_Win_Mode == INIT_WIN_MODE) {
                    // Switch to Mac mode
                    Keyboard_Info.Mac_Win_Mode = INIT_MAC_MODE;
                    Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;  // Unlock Win key in Mac mode
                    Mac_Win_Point_Count = 3;  // Blink 3 times for Mac mode
                    layer_on(1);  // Switch to Mac layer
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                } else {
                    // Switch to Windows mode
                    Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
                    Mac_Win_Point_Count = 1;  // Blink 1 time for Windows mode
                    layer_off(1);  // Switch to Windows layer (layer 0)
                    unregister_code(KC_LALT); unregister_code(KC_LGUI); unregister_code(KC_RALT); unregister_code(KC_RGUI); unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
        } return true;
        default:    return true; // Process all other keycodes normally
    }
}
