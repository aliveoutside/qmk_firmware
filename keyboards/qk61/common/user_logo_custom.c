/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
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

#include "rdmctmzt_common.h"

uint8_t Logo_Flash_Count = 0;
uint8_t Logo_Led_Count = 0;
uint8_t Logo_Play_Point = 0;
uint8_t Logo_Pwm_R = 0;
uint8_t Logo_Pwm_G = 0;
uint8_t Logo_Pwm_B = 0;

uint8_t Logo_Index_Tab[LOGO_LED_SIZE] = {61, 62, 63};

uint8_t LED_Mix_Colour_Tab[256][3] = {
    {255,   0,   0},
    {255,   1,   0},
    {255,   3,   0},
    {255,   4,   0},
    {255,   7,   0},
    {255,   8,   0},
    {255,  10,   0},
    {255,  12,   0},
    {255,  14,   0},
    {255,  15,   0},
    {255,  17,   0},
    {255,  21,   0},
    {255,  24,   0},
    {255,  27,   0},
    {255,  30,   0},
    {255,  35,   0},
    {255,  38,   0},
    {255,  41,   0},
    {255,  44,   0},
    {255,  45,   0},
    {255,  48,   0},
    {255,  51,   0},
    {255,  55,   0},
    {255,  58,   0},
    {255,  62,   0},
    {255,  64,   0},
    {255,  68,   0},
    {255,  71,   0},
    {255,  74,   0},
    {255,  78,   0},
    {255,  80,   0},
    {255,  82,   0},
    {255,  84,   0},
    {255,  88,   0},
    {255,  90,   0},
    {255,  95,   0},
    {255, 100,   0},
    {255, 103,   0},
    {255, 107,   0},
    {255, 110,   0},
    {255, 113,   0},
    {255, 117,   0},
    {255, 120,   0},
    {255, 124,   0},
    {255, 128,   0},
    {255, 130,   0},
    {255, 132,   0},
    {255, 136,   0},
    {255, 140,   0},
    {255, 142,   0},
    {255, 147,   0},
    {255, 149,   0},
    {255, 151,   0},
    {255, 153,   0},
    {255, 158,   0},
    {255, 160,   0},
    {255, 162,   0},
    {255, 168,   0},
    {255, 171,   0},
    {255, 174,   0},
    {255, 177,   0},
    {255, 180,   0},
    {255, 183,   0},
    {255, 187,   0},
    {255, 190,   0},
    {255, 193,   0},
    {255, 196,   0},
    {255, 199,   0},
    {255, 201,   0},
    {255, 205,   0},
    {255, 208,   0},
    {255, 212,   0},
    {255, 220,   0},
    {255, 225,   0},
    {255, 230,   0},
    {255, 235,   0},
    {255, 238,   0},
    {255, 240,   0},
    {255, 245,   0},
    {255, 250,   0},
    {255, 254,   0},
    {255, 255,   0},
    {245, 255,   0},
    {231, 255,   0},
    {224, 255,   0},
    {217, 255,   0},
    {203, 255,   0},
    {196, 255,   0},
    {189, 255,   0},
    {175, 255,   0},
    {168, 255,   0},
    {161, 255,   0},
    {147, 255,   0},
    {140, 255,   0},
    {133, 255,   0},
    {126, 255,   0},
    {119, 255,   0},
    {105, 255,   0},
    { 98, 255,   0},
    { 91, 255,   0},
    { 84, 255,   0},
    { 77, 255,   0},
    { 70, 255,   0},
    { 63, 255,   0},
    { 56, 255,   0},
    { 49, 255,   0},
    { 42, 255,   0},
    { 35, 255,   0},
    { 28, 255,   0},
    { 21, 255,   0},
    { 14, 255,   0},
    {  7, 255,   0},
    {  0, 255,   0},
    {  0, 255,   7},
    {  0, 255,  14},
    {  0, 255,  21},
    {  0, 255,  28},
    {  0, 255,  35},
    {  0, 255,  42},
    {  0, 255,  49},
    {  0, 255,  56},
    {  0, 255,  63},
    {  0, 255,  70},
    {  0, 255,  77},
    {  0, 255,  84},
    {  0, 255,  91},
    {  0, 255,  98},
    {  0, 255, 105},
    {  0, 255, 119},
    {  0, 255, 126},
    {  0, 255, 133},
    {  0, 255, 140},
    {  0, 255, 154},
    {  0, 255, 161},
    {  0, 255, 168},
    {  0, 255, 182},
    {  0, 255, 189},
    {  0, 255, 196},
    {  0, 255, 210},
    {  0, 255, 217},
    {  0, 255, 224},
    {  0, 255, 238},
    {  0, 255, 245},
    {  0, 255, 255},
    {  0, 245, 255},
    {  0, 231, 255},
    {  0, 224, 255},
    {  0, 217, 255},
    {  0, 203, 255},
    {  0, 196, 255},
    {  0, 189, 255},
    {  0, 175, 255},
    {  0, 168, 255},
    {  0, 161, 255},
    {  0, 147, 255},
    {  0, 140, 255},
    {  0, 133, 255},
    {  0, 126, 255},
    {  0, 119, 255},
    {  0, 105, 255},
    {  0,  98, 255},
    {  0,  91, 255},
    {  0,  84, 255},
    {  0,  77, 255},
    {  0,  70, 255},
    {  0,  63, 255},
    {  0,  56, 255},
    {  0,  49, 255},
    {  0,  42, 255},
    {  0,  35, 255},
    {  0,  28, 255},
    {  0,  21, 255},
    {  0,  14, 255},
    {  0,   7, 255},
    {  0,   0, 255},
    {  5,   0, 255},
    { 10,   0, 255},
    { 15,   0, 255},
    { 20,   0, 255},
    { 25,   0, 255},
    { 30,   0, 255},
    { 35,   0, 255},
    { 40,   0, 255},
    { 45,   0, 255},
    { 50,   0, 255},
    { 55,   0, 255},
    { 60,   0, 255},
    { 65,   0, 255},
    { 70,   0, 255},
    { 75,   0, 255},
    { 85,   0, 255},
    { 90,   0, 255},
    { 95,   0, 255},
    {100,   0, 255},
    {105,   0, 255},
    {110,   0, 255},
    {115,   0, 255},
    {120,   0, 255},
    {125,   0, 255},
    {130,   0, 255},
    {135,   0, 255},
    {140,   0, 255},
    {145,   0, 255},
    {150,   0, 255},
    {155,   0, 255},
    {160,   0, 255},
    {165,   0, 255},
    {170,   0, 255},
    {175,   0, 255},
    {185,   0, 255},
    {180,   0, 255},
    {195,   0, 255},
    {190,   0, 255},
    {200,   0, 255},
    {205,   0, 255},
    {210,   0, 255},
    {215,   0, 255},
    {220,   0, 255},
    {225,   0, 255},
    {230,   0, 255},
    {235,   0, 255},
    {240,   0, 255},
    {245,   0, 255},
    {250,   0, 255},
    {255,   0, 255},
    {255,   0, 255},
    {255,   0, 245},
    {255,   0, 231},
    {255,   0, 224},
    {255,   0, 210},
    {255,   0, 203},
    {255,   0, 196},
    {255,   0, 182},
    {255,   0, 175},
    {255,   0, 168},
    {255,   0, 161},
    {255,   0, 147},
    {255,   0, 140},
    {255,   0, 133},
    {255,   0, 126},
    {255,   0, 119},
    {255,   0, 105},
    {255,   0,  98},
    {255,   0,  91},
    {255,   0,  84},
    {255,   0,  77},
    {255,   0,  70},
    {255,   0,  63},
    {255,   0,  56},
    {255,   0,  49},
    {255,   0,  42},
    {255,   0,  35},
    {255,   0,  28},
    {255,   0,  21},
    {255,   0,  14},
    {255,   0,   7},
};

void Logo_Init(void) {
    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        rgb_matrix_set_color(Logo_Index_Tab[i], 0, 0, 0);
    }

    Logo_Play_Point = 64;
    Logo_Pwm_R = 0;
    Logo_Pwm_G = 0;
    Logo_Pwm_B = 0;
}

void Logo_Pwm_Rgb_Updata(uint8_t val) {
    Logo_Pwm_R = (((Logo_Pwm_R | Keyboard_Info.Logo_Saturation) * val) >> 8);
    Logo_Pwm_G = (((Logo_Pwm_G | Keyboard_Info.Logo_Saturation) * val) >> 8);
    Logo_Pwm_B = (((Logo_Pwm_B | Keyboard_Info.Logo_Saturation) * val) >> 8);
}

void Logo_Pwm_Ds_Updata(uint8_t val) {
    Logo_Pwm_R = (((((Logo_Pwm_R * val) >> 8) | Keyboard_Info.Logo_Saturation) * Keyboard_Info.Logo_Brightness) >> 8);
    Logo_Pwm_G = (((((Logo_Pwm_G * val) >> 8) | Keyboard_Info.Logo_Saturation) * Keyboard_Info.Logo_Brightness) >> 8);
    Logo_Pwm_B = (((((Logo_Pwm_B * val) >> 8) | Keyboard_Info.Logo_Saturation) * Keyboard_Info.Logo_Brightness) >> 8);
}

void Logo_Off_mode_Show(void) {
    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        rgb_matrix_set_color(Logo_Index_Tab[i], 0, 0, 0);
    }
}

void Logo_Wave_Rgb_mode_Show(void) {
    if (Logo_Led_Count) {
        Logo_Led_Count = 0;

        if (Keyboard_Info.Logo_Speed) {
            if (Keyboard_Info.Logo_Speed > Logo_Play_Point) {
                Logo_Play_Point = (Logo_Play_Point - 1) - Keyboard_Info.Logo_Speed;
            } else {
                Logo_Play_Point = Logo_Play_Point - Keyboard_Info.Logo_Speed;
            }
        }
    }

    uint8_t index = Logo_Play_Point;

    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        Logo_Pwm_R = LED_Mix_Colour_Tab[index][0];
        Logo_Pwm_G = LED_Mix_Colour_Tab[index][1];
        Logo_Pwm_B = LED_Mix_Colour_Tab[index][2];

        Logo_Pwm_Rgb_Updata(Keyboard_Info.Logo_Brightness);

        rgb_matrix_set_color(Logo_Index_Tab[i], Logo_Pwm_R, Logo_Pwm_G, Logo_Pwm_B);

        index += 12;
        if (index == 255) {
            index = 0;
        }
    }
}

void Logo_Spectrum_mode_Show(void) {
    if (Logo_Led_Count) {
        Logo_Led_Count = 0;

        if (Keyboard_Info.Logo_Speed) {
            if (Keyboard_Info.Logo_Speed > Logo_Play_Point) {
                Logo_Play_Point = (Logo_Play_Point - 1) - Keyboard_Info.Logo_Speed;
            } else {
                Logo_Play_Point = Logo_Play_Point - Keyboard_Info.Logo_Speed;
            }
        }
    }

    Logo_Pwm_R = LED_Mix_Colour_Tab[Logo_Play_Point][0];
    Logo_Pwm_G = LED_Mix_Colour_Tab[Logo_Play_Point][1];
    Logo_Pwm_B = LED_Mix_Colour_Tab[Logo_Play_Point][2];

    Logo_Pwm_Rgb_Updata(Keyboard_Info.Logo_Brightness);

    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        rgb_matrix_set_color(Logo_Index_Tab[i], Logo_Pwm_R, Logo_Pwm_G, Logo_Pwm_B);
    }
}

void Logo_Wave_Ds_mode_Show(void) {
    if (Logo_Led_Count) {
        Logo_Led_Count = 0;

        if (Keyboard_Info.Logo_Speed) {
            if (Keyboard_Info.Logo_Speed > Logo_Play_Point) {
                Logo_Play_Point = (Logo_Play_Point + 127) - Keyboard_Info.Logo_Speed;
            } else {
                Logo_Play_Point = Logo_Play_Point - Keyboard_Info.Logo_Speed;
            }
        }
    }

    uint8_t index = Logo_Play_Point;

    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        Logo_Pwm_R = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][0];
        Logo_Pwm_G = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][1];
        Logo_Pwm_B = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][2];

        Logo_Pwm_Ds_Updata(Led_Wave_Pwm_Tab[index]);

        rgb_matrix_set_color(Logo_Index_Tab[i], Logo_Pwm_R, Logo_Pwm_G, Logo_Pwm_B);

        index += 8;
        if (index > 126) {
            index = 0;
        }
    }
}

void Logo_Breath_mode_Show(void) {
    if (Logo_Led_Count) {
        Logo_Led_Count = 0;

        if (Keyboard_Info.Logo_Speed) {
            if (Keyboard_Info.Logo_Speed > Logo_Play_Point) {
                Logo_Play_Point = (Logo_Play_Point + 127) - Keyboard_Info.Logo_Speed;
            } else {
                Logo_Play_Point = Logo_Play_Point - Keyboard_Info.Logo_Speed;
            }
        }
    }

    Logo_Pwm_R = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][0];
    Logo_Pwm_G = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][1];
    Logo_Pwm_B = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][2];

    Logo_Pwm_Ds_Updata(Led_Wave_Pwm_Tab[Logo_Play_Point]);

    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        rgb_matrix_set_color(Logo_Index_Tab[i], Logo_Pwm_R, Logo_Pwm_G, Logo_Pwm_B);
    }
}

void Logo_Light_mode_Show(void) {
    Logo_Pwm_R = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][0];
    Logo_Pwm_G = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][1];
    Logo_Pwm_B = LED_Mix_Colour_Tab[Keyboard_Info.Logo_Colour][2];

    Logo_Pwm_Ds_Updata(255);

    for (uint8_t i = 0; i < LOGO_LED_SIZE; i++) {
        rgb_matrix_set_color(Logo_Index_Tab[i], Logo_Pwm_R, Logo_Pwm_G, Logo_Pwm_B);
    }
}

void Logo_Mode_Show(void) {
    if (Keyboard_Info.Logo_On_Off) {
        Logo_Off_mode_Show();
        return;
    }

    switch (Keyboard_Info.Logo_Mode) {
        case LOGO_WAVE_RGB_MODE: Logo_Wave_Rgb_mode_Show(); break;
        case LOGO_WAVE_DS_MODE:  Logo_Wave_Ds_mode_Show();  break;
        case LOGO_SPECTRUM_MODE: Logo_Spectrum_mode_Show(); break;
        case LOGO_BREATH_MODE:   Logo_Breath_mode_Show();   break;
        case LOGO_LIGHT_MODE:    Logo_Light_mode_Show();    break;
        default:                 Logo_Off_mode_Show();      break;
    }
}

void User_Via_Qmk_Logo_Set_Value(uint8_t *data) {
    switch (data[0]) {
        case id_qmk_rgblight_brightness: {
            if (data[1] > LOGO_MAX_BRIGHTNESS) {
                Keyboard_Info.Logo_Brightness = LOGO_MAX_BRIGHTNESS;
            } else {
                Keyboard_Info.Logo_Brightness = data[1];
            }
        } break;
        case id_qmk_rgblight_effect: {
            if (data[1] == 0) {
                Keyboard_Info.Logo_On_Off = LOGO_LED_OFF;
            } else {
                Keyboard_Info.Logo_On_Off = LOGO_LED_ON;
                if (data[1] <= LOGO_OFF_MODE) {
                    Keyboard_Info.Logo_Mode = data[1];
                } else {
                    Keyboard_Info.Logo_Mode = LOGO_WAVE_RGB_MODE;
                }
            }
        } break;
        case id_qmk_rgblight_effect_speed: {
            if (data[1] > LOGO_MAX_SPEED) {
                Keyboard_Info.Logo_Speed = LOGO_MAX_SPEED;
            } else {
                Keyboard_Info.Logo_Speed = data[1];
            }
        } break;
        case id_qmk_rgblight_color: {
            Keyboard_Info.Logo_Colour     = data[1];
            Keyboard_Info.Logo_Saturation = (uint8_t)(~data[2]);
        } break;
        default: break;
    }
}

void User_Via_Qmk_Logo_Get_Value(uint8_t *data) {
    switch (data[0]) {
        case id_qmk_rgblight_brightness: {
            data[1] = Keyboard_Info.Logo_Brightness;
        } break;
        case id_qmk_rgblight_effect: {
            data[1] = Keyboard_Info.Logo_Mode;
        } break;
        case id_qmk_rgblight_effect_speed: {
            data[1] = Keyboard_Info.Logo_Speed;
        } break;
        case id_qmk_rgblight_color: {
            data[1] = Keyboard_Info.Logo_Colour;
            data[2] = (uint8_t)(~Keyboard_Info.Logo_Saturation);
        } break;
        default: break;
    }
}

void User_Via_Qmk_Logo_Command(uint8_t *data, uint8_t length) {
    (void)length;

    switch (data[0]) {
        case id_custom_set_value: User_Via_Qmk_Logo_Set_Value(&(data[2])); break;
        case id_custom_get_value: User_Via_Qmk_Logo_Get_Value(&(data[2])); break;
        case id_custom_save:      Save_Flash_Set();                        break;
        default:                  data[0] = id_unhandled;                  break;
    }
}
