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

#pragma once

#include <stdint.h>

extern uint8_t Logo_Flash_Count;
extern uint8_t Logo_Led_Count;
extern uint8_t Logo_Play_Point;
extern uint8_t Logo_Pwm_R;
extern uint8_t Logo_Pwm_G;
extern uint8_t Logo_Pwm_B;

extern uint8_t LED_Mix_Colour_Tab[256][3];
extern uint8_t Logo_Index_Tab[3];

void Logo_Init(void);
void Logo_Mode_Show(void);

void User_Via_Qmk_Logo_Get_Value(uint8_t *data);
void User_Via_Qmk_Logo_Set_Value(uint8_t *data);
void User_Via_Qmk_Logo_Command(uint8_t *data, uint8_t length);
