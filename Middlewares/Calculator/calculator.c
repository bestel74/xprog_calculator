/*
 * calculator.c
 *
 *  Created on: 23 sept. 2020
 *      Author: steven
 */
#include "calculator.h"
#include "display.h"
#include "keypad.h"




osThreadId calculatorTaskHandle;
osPoolDef(mpool_calculator, 16, S_CALC_MSG);
osPoolId  mpool_calculator;
osMessageQDef(msgbox_calculator, 16, S_CALC_MSG*);
osMessageQId  msgbox_calculator;




typedef struct
{
    E_DISPLAY_MODE mode;
    E_DISPLAY_BINARY_COLOR bin_color;

    uint32_t number;
    uint32_t saved_number;

    uint8_t op_keycode;
} S_CALC_CURRENT;


S_CALC_CURRENT calc =
{
    .mode = E_DISPLAY_MODE_DEC,
    .bin_color = E_DISPLAY_BINARY_COLOR_BLUE,

    .number = 0,
    .saved_number = 0,
    .op_keycode = 0,
};




void calculator_handleKey(E_KEYPAD_KEY key);
void calculator_changeMode();
void calculator_clear();
void calculator_newKey(E_KEYPAD_KEY key);
void calculator_changeOperator(E_KEYPAD_KEY key);
void calculator_changeSetting();
void calculator_enter();
void calculator_display_mode(E_DISPLAY_MODE mode);
void calculator_display_number(uint32_t number);




void calculator_Task_create()
{
    osThreadDef(calculatorTask, calculator_Task_entry, osPriorityNormal, 0, 512);
    calculatorTaskHandle = osThreadCreate(osThread(calculatorTask), NULL);

    calculator_init();
}


void calculator_Task_entry(void const * argument)
{
    osEvent  evt;
    S_CALC_MSG *msg;

    /* Infinite loop */
    for(;;)
    {
        evt = osMessageGet(msgbox_calculator, osWaitForever);  // wait for message
        if (evt.status == osEventMessage)
        {
            msg = evt.value.p;
            switch(msg->msgid)
            {
                case E_CALC_MSG_ID_KEY_PRESS:
                {
                    calculator_handleKey(msg->data.key);
                }
            }

            osPoolFree(mpool_calculator, msg);
        }
    }
}


void calculator_handleKey(E_KEYPAD_KEY key)
{
    switch(key)
    {
        case E_KEYPAD_KEY_0:
        case E_KEYPAD_KEY_1:
        case E_KEYPAD_KEY_2:
        case E_KEYPAD_KEY_3:
        case E_KEYPAD_KEY_4:
        case E_KEYPAD_KEY_5:
        case E_KEYPAD_KEY_6:
        case E_KEYPAD_KEY_7:
        case E_KEYPAD_KEY_8:
        case E_KEYPAD_KEY_9:
        case E_KEYPAD_KEY_A:
        case E_KEYPAD_KEY_B:
        case E_KEYPAD_KEY_C:
        case E_KEYPAD_KEY_D:
        case E_KEYPAD_KEY_E:
        case E_KEYPAD_KEY_F:
        {
            calculator_newKey(key);
            break;
        }

        case E_KEYPAD_KEY_PLUS:
        case E_KEYPAD_KEY_MINUS:
        case E_KEYPAD_KEY_MULT:
        case E_KEYPAD_KEY_DIV:
        {
            calculator_changeOperator(key);
            break;
        }

        case E_KEYPAD_KEY_EQUAL:
        {
            calculator_enter();
            break;
        }

        case E_KEYPAD_KEY_MODE:
        {
            calculator_changeMode();
            break;
        }

        case E_KEYPAD_KEY_SETTING:
        {
            calculator_changeSetting();
            break;
        }

        case E_KEYPAD_KEY_CLEAR:
        {
            calculator_clear();
            break;
        }
    }
}


void calculator_sendEventKey(S_CALC_MSG msg)
{
    S_CALC_MSG *m;

    m = osPoolAlloc(mpool_calculator);
    if(m)
    {
        m->msgid = msg.msgid;
        m->data.key = msg.data.key;
        osMessagePut(msgbox_calculator, (uint32_t)m, osWaitForever);
    }
}




void calculator_init()
{

}


void calculator_changeMode()
{
    // Do not change LSB Mode
    uint8_t cm = calc.mode & ~(E_DISPLAY_MODE_LSD);
    cm = cm << 1;

    // Only 3 mode, 0x01, 0x02 and 0x04
    if(cm > 0x08)
    {
        cm = 0x01;
    }
    // Merge new mode with actual LSB Mode
    calc.mode = (calc.mode & E_DISPLAY_MODE_LSD) | (cm & ~(E_DISPLAY_MODE_LSD));

    calculator_display_mode(calc.mode);
}


void calculator_clear()
{
    calc.number = 0;
    calc.saved_number = 0;

    calculator_display_number(calc.number);
}


void calculator_newKey(uint8_t keycode)
{
    uint8_t cm = calc.mode & 0x0f;

    switch(cm)
    {
        case E_DISPLAY_MODE_BIN:
        {
            if(keycode <= E_KEYPAD_KEY_1)
            {
                calc.number = (calc.number << 1) | keycode;
            }
        }

        case E_DISPLAY_MODE_DEC:
        {
            if(keycode <= E_KEYPAD_KEY_9)
            {
                calc.number = (calc.number * 10) + keycode;
            }
        }

        case E_DISPLAY_MODE_HEX:
        {
            if(keycode <= E_KEYPAD_KEY_F)
            {
                calc.number = (calc.number << 4) | keycode;
            }
        }
    }

    calculator_display_number(calc.number);
}


void calculator_changeOperator(E_KEYPAD_KEY keycode)
{
    // Chain of operation? (Without pressing '=')
    if(calc.saved_number != 0 && calc.number != 0)
    {
        switch(calc.op_keycode)
        {
            case E_KEYPAD_KEY_PLUS:
            {
                calc.saved_number += calc.number;
            }

            case E_KEYPAD_KEY_MINUS:
            {
                calc.saved_number -= calc.number;
            }

            case E_KEYPAD_KEY_MULT:
            {
                calc.saved_number *= calc.number;
            }

            case E_KEYPAD_KEY_DIV:
            {
                calc.saved_number /= calc.number;
            }
        }

        calc.number = 0;
        calculator_display_number(calc.saved_number);
    }
    // First time pressing an operator?
    else if(calc.number != 0)
    {
        calc.saved_number = calc.number;
        calc.number = 0;
    }

    calc.op_keycode = keycode;
}


void calculator_changeSetting()
{
    // For the moment, just change the color
    if(calc.bin_color == E_DISPLAY_BINARY_COLOR_BLUE)
    {
        calc.bin_color = E_DISPLAY_BINARY_COLOR_GREEN;
    }
    else
    {
        calc.bin_color = E_DISPLAY_BINARY_COLOR_BLUE;
    }

    // And flip LSB mode
    calc.mode ^= E_DISPLAY_MODE_LSD;

    calculator_display_mode(calc.mode);
}


void calculator_enter()
{
    switch(calc.op_keycode)
    {
        case E_KEYPAD_KEY_PLUS:
        {
            calc.saved_number += calc.number;
        }

        case E_KEYPAD_KEY_MINUS:
        {
            calc.saved_number -= calc.number;
        }

        case E_KEYPAD_KEY_MULT:
        {
            calc.saved_number *= calc.number;
        }

        case E_KEYPAD_KEY_DIV:
        {
            if(calc.number != 0)
            {
                calc.saved_number /= calc.number;
            }
        }
    }

    calc.number = 0;
    calculator_display_number(calc.saved_number);
}


void calculator_display_mode(E_DISPLAY_MODE mode)
{
    S_DISPLAY_MSG m;
    m.msgid = E_DISPLAY_MSG_ID_DISPLAY_MODE;
    m.data.mode = mode;

    display_sendMsg(m);
}


void calculator_display_number(uint32_t number)
{
    S_DISPLAY_MSG m;
    m.msgid = E_DISPLAY_MSG_ID_DISPLAY_NUMBER;
    m.data.num.number = number;
    m.data.num.mode = calc.mode;

    display_sendMsg(m);
}
