/*
 * display.h
 *
 *  Created on: 22 sept. 2020
 *      Author: steven
 */

#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_


#include "cmsis_os.h"



typedef enum
{
    E_DISPLAY_MODE_BIN = 0x01,
    E_DISPLAY_MODE_DEC = 0x02,
    E_DISPLAY_MODE_HEX = 0x04,
    E_DISPLAY_MODE_LSD = 0x10,
} E_DISPLAY_MODE;

typedef enum
{
    E_DISPLAY_BINARY_COLOR_BLUE,
    E_DISPLAY_BINARY_COLOR_GREEN
} E_DISPLAY_BINARY_COLOR;




typedef struct
{
    E_DISPLAY_BINARY_COLOR bin_color;
    E_DISPLAY_MODE mode;
    uint32_t number;
} S_DISPLAY_NUMBER;

typedef struct
{
    union
    {
        struct
        {
            uint8_t a: 1;
            uint8_t b: 1;
            uint8_t c: 1;
            uint8_t d: 1;
            uint8_t e: 1;
            uint8_t f: 1;
            uint8_t g: 1;
        };
        uint8_t value;
    };
}S_DIGIT;




typedef enum
{
    E_DISPLAY_MSG_ID_DISPLAY_MODE,
    E_DISPLAY_MSG_ID_DISPLAY_NUMBER
} E_DISPLAY_MSG_ID;

typedef struct
{
    E_DISPLAY_MSG_ID  msgid;

    union
    {
        E_DISPLAY_MODE mode;
        S_DISPLAY_NUMBER num;
    } data;

} S_DISPLAY_MSG;




void display_Task_create();
void display_Task_entry(void const * argument);
void display_sendMsg(S_DISPLAY_MSG msg_id);

void display_init();


#endif /* DISPLAY_DISPLAY_H_ */
