/*
 * calculator.h
 *
 *  Created on: 23 sept. 2020
 *      Author: steven
 */

#ifndef CALCULATOR_CALCULATOR_H_
#define CALCULATOR_CALCULATOR_H_

#include "cmsis_os.h"
#include "keypad.h"


typedef enum
{
    E_CALC_MSG_ID_KEY_PRESS
} E_CALC_MSG_ID;

typedef struct
{
    E_CALC_MSG_ID  msgid;

    union
    {
        E_KEYPAD_KEY key;
    } data;
} S_CALC_MSG;




void calculator_Task_create();
void calculator_Task_entry(void const * argument);
void calculator_sendEventKey(S_CALC_MSG msg);


void calculator_init();


#endif /* CALCULATOR_CALCULATOR_H_ */
