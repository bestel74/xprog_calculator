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
    E_SELECT_MODE_BIN = 0x01,
    E_SELECT_MODE_DEC = 0x02,
    E_SELECT_MODE_HEX = 0x04,
    E_SELECT_MODE_LSD = 0x08,
} E_SELECT_MODE;

typedef struct
{
    union
    {
        E_SELECT_MODE mode;
        uint8_t value;
    };
} S_SELECT_MODE;

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
        S_SELECT_MODE mode;
        uint32_t number;
    } data;

} S_DISPLAY_MSG;




void display_Task_create();
void display_Task_entry(void const * argument);
void display_sendMsg(E_DISPLAY_MSG_ID msg_id);

void display_init();


#endif /* DISPLAY_DISPLAY_H_ */
