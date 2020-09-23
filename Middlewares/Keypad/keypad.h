/*
 * keypad.h
 *
 *  Created on: 23 sept. 2020
 *      Author: steven
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

#include "cmsis_os.h"


#define KEYPAD_OUTPUT_PINS     4
#define KEYPAD_INPUT_PINS      6




typedef enum
{
    E_KEYPAD_KEY_0,
    E_KEYPAD_KEY_1,
    E_KEYPAD_KEY_2,
    E_KEYPAD_KEY_3,
    E_KEYPAD_KEY_4,
    E_KEYPAD_KEY_5,
    E_KEYPAD_KEY_6,
    E_KEYPAD_KEY_7,
    E_KEYPAD_KEY_8,
    E_KEYPAD_KEY_9,
    E_KEYPAD_KEY_A,
    E_KEYPAD_KEY_B,
    E_KEYPAD_KEY_C,
    E_KEYPAD_KEY_D,
    E_KEYPAD_KEY_E,
    E_KEYPAD_KEY_F,

    E_KEYPAD_KEY_PLUS,
    E_KEYPAD_KEY_MINUS,
    E_KEYPAD_KEY_MULT,
    E_KEYPAD_KEY_DIV,
    E_KEYPAD_KEY_EQUAL,
    E_KEYPAD_KEY_MODE,
    E_KEYPAD_KEY_SETTING,
    E_KEYPAD_KEY_CLEAR,
} E_KEYPAD_KEY;

typedef enum
{
    E_KEYPAD_KEY_EVENT_RELEASE = 0,
    E_KEYPAD_KEY_EVENT_PRESS,
} E_KEYPAD_KEY_EVENT;


typedef struct
{
    E_KEYPAD_KEY key;
    E_KEYPAD_KEY_EVENT event;
} S_KEYPAD_KEY_EVENT;




typedef enum
{
    E_KEYPAD_MSG_ID_REFRESH,
} E_KEYPAD_MSG_ID;

typedef struct
{
  E_KEYPAD_MSG_ID  msgid;
} S_KEYPAD_MSG;




void keypad_Task_create();
void keypad_Task_entry(void const * argument);
void keypad_sendMsg(E_KEYPAD_MSG_ID msg_id);

void keypad_init();


#endif /* KEYPAD_KEYPAD_H_ */
