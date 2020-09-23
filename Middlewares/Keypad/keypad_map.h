/*
 * keypad_mapping.h
 *
 *  Created on: 23 sept. 2020
 *      Author: steven
 */

#ifndef KEYPAD_KEYPAD_MAP_H_
#define KEYPAD_KEYPAD_MAP_H_


#include "main.h"


typedef struct
{
    uint8_t id;
    GPIO_TypeDef* gpio;
    uint16_t pin;
} S_KEYPAD_IO;


S_KEYPAD_IO keypad_map_output[KEYPAD_OUTPUT_PINS] =
{
    // First line = TOP
    {
        .id = 0,
        .gpio = KEYPAD_OUTPUT_ROW_0_GPIO_Port,
        .pin = KEYPAD_OUTPUT_ROW_0_Pin,
    },
    {
        .id = 1,
        .gpio = KEYPAD_OUTPUT_ROW_1_GPIO_Port,
        .pin = KEYPAD_OUTPUT_ROW_1_Pin,
    },
    {
        .id = 2,
        .gpio = KEYPAD_OUTPUT_ROW_2_GPIO_Port,
        .pin = KEYPAD_OUTPUT_ROW_2_Pin,
    },
    {
        .id = 3,
        .gpio = KEYPAD_OUTPUT_ROW_3_GPIO_Port,
        .pin = KEYPAD_OUTPUT_ROW_3_Pin,
    },
};


S_KEYPAD_IO keypad_map_input[KEYPAD_INPUT_PINS] =
{
    // First line = LEFT
    {
        .id = 0,
        .gpio = KEYPAD_INPUT_COL_0_GPIO_Port,
        .pin = KEYPAD_INPUT_COL_0_Pin,
    },
    {
        .id = 1,
        .gpio = KEYPAD_INPUT_COL_1_GPIO_Port,
        .pin = KEYPAD_INPUT_COL_1_Pin,
    },
    {
        .id = 2,
        .gpio = KEYPAD_INPUT_COL_2_GPIO_Port,
        .pin = KEYPAD_INPUT_COL_2_Pin,
    },
    {
        .id = 3,
        .gpio = KEYPAD_INPUT_COL_3_GPIO_Port,
        .pin = KEYPAD_INPUT_COL_3_Pin,
    },
    {
        .id = 4,
        .gpio = KEYPAD_INPUT_COL_4_GPIO_Port,
        .pin = KEYPAD_INPUT_COL_4_Pin,
    },
    {
        .id = 5,
        .gpio = KEYPAD_INPUT_COL_5_GPIO_Port,
        .pin = KEYPAD_INPUT_COL_5_Pin,
    },
};

E_KEYPAD_KEY keypad_map_table[KEYPAD_OUTPUT_PINS][KEYPAD_INPUT_PINS] =
{
    {
        E_KEYPAD_KEY_7, E_KEYPAD_KEY_8, E_KEYPAD_KEY_9, E_KEYPAD_KEY_F, E_KEYPAD_KEY_DIV, E_KEYPAD_KEY_CLEAR,
    },
    {
        E_KEYPAD_KEY_4, E_KEYPAD_KEY_5, E_KEYPAD_KEY_6, E_KEYPAD_KEY_E, E_KEYPAD_KEY_MULT, E_KEYPAD_KEY_SETTING,
    },
    {
        E_KEYPAD_KEY_1, E_KEYPAD_KEY_2, E_KEYPAD_KEY_3, E_KEYPAD_KEY_D, E_KEYPAD_KEY_MINUS, E_KEYPAD_KEY_MODE,
    },
    {
        E_KEYPAD_KEY_0, E_KEYPAD_KEY_A, E_KEYPAD_KEY_B, E_KEYPAD_KEY_C, E_KEYPAD_KEY_PLUS, E_KEYPAD_KEY_EQUAL,
    },
};

E_KEYPAD_KEY keypad_map_convert(S_KEYPAD_IO *out, S_KEYPAD_IO *in)
{
    E_KEYPAD_KEY key = 255;

    if(out && in)
    {
        key = keypad_map_table[out->id][in->id];
    }

    return key;
}



#endif /* KEYPAD_KEYPAD_MAP_H_ */
