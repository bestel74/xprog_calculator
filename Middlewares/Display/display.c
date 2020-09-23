/*
 * display.c
 *
 *  Created on: 22 sept. 2020
 *      Author: steven
 */
#include "stdio.h"
#include "display.h"
#include "ch423.h"


extern TIM_HandleTypeDef htim2;


osThreadId displayTaskHandle;
osPoolDef(mpool_display, 16, S_DISPLAY_MSG);
osPoolId  mpool_display;
osMessageQDef(msgbox_display, 16, S_DISPLAY_MSG*);
osMessageQId  msgbox_display;




void display_mode(E_DISPLAY_MODE mode);
void display_number(S_DISPLAY_NUMBER num);

void display_binary(S_DISPLAY_NUMBER num);
void display_decimal(S_DISPLAY_NUMBER num);
void display_hexa(S_DISPLAY_NUMBER num);
uint8_t display_convertToDigit(char num);



void display_Task_create()
{
    osThreadDef(displayTask, display_Task_entry, osPriorityNormal, 0, 512);
    displayTaskHandle = osThreadCreate(osThread(displayTask), NULL);

    display_init();
}


void display_Task_entry(void const * argument)
{
    osEvent  evt;
    S_DISPLAY_MSG *msg;

    /* Infinite loop */
    for(;;)
    {
        evt = osMessageGet(msgbox_display, osWaitForever);  // wait for message
        if (evt.status == osEventMessage) {
            msg = evt.value.p;
            switch(msg->msgid)
            {
                case E_DISPLAY_MSG_ID_DISPLAY_MODE:
                {
                    display_mode(msg->data.mode);
                    break;
                }

                case E_DISPLAY_MSG_ID_DISPLAY_NUMBER:
                {
                    display_number(msg->data.num);
                    break;
                }
            }

            osPoolFree(mpool_display, msg);
        }
    }
}


void display_sendMsg(S_DISPLAY_MSG msg)
{
    // Screen refresh
    S_DISPLAY_MSG    *m;

    m = osPoolAlloc(mpool_display);
    if(m)
    {
        m->msgid = msg.msgid;
        m->data = msg.data;
        osMessagePut(msgbox_display, (uint32_t)m, osWaitForever);
    }
}




void display_init()
{
    while(ch423_init() != 0)
    {
        HAL_Delay(1);
    }
}

void display_mode(E_DISPLAY_MODE mode)
{
    if(mode == E_DISPLAY_MODE_BIN)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
    }

    if(mode == E_DISPLAY_MODE_DEC)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
    }

    if(mode == E_DISPLAY_MODE_HEX)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
    }

    if(mode == E_DISPLAY_MODE_LSD)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
    }
}



void display_number(S_DISPLAY_NUMBER num)
{
    display_binary(num);
    display_decimal(num);
    display_hexa(num);
}


// Blue  = b00 - b07 = DIG0
//         b08 - b15 = DIG2
//         b16 - b23 = DIG4
//         b24 - b31 = DIG6

// Green = b00 - b07 = DIG1
//         b08 - b15 = DIG3
//         b16 - b23 = DIG5
//         b24 - b31 = DIG7
void display_binary(S_DISPLAY_NUMBER num)
{
    uint8_t disp_number = 0;
    uint8_t digit_number = 0;

    for(int8_t i=0 ; i < 4 ; i++)
    {
        switch(num.bin_color)
        {
            case E_DISPLAY_BINARY_COLOR_BLUE:
            {
                disp_number = (num.number >> i*8) & 0xFF;
                digit_number = i*2;
            }
            case E_DISPLAY_BINARY_COLOR_GREEN:
            {
                disp_number = (num.number >> i*8) & 0xFF;
                digit_number = i*2 +1;
            }
        }

        // Display '1' with 'on' color setting
        while(ch423_setDigit(E_DISPLAY_BINARY, digit_number, disp_number) != 0)
        {
            osDelay(1);
        }
    }

    // Turn off secondary color channel
    for(int8_t i=0 ; i < 4 ; i++)
    {
        switch(num.bin_color)
        {
            case E_DISPLAY_BINARY_COLOR_BLUE:
            {
                digit_number = i*2 +1;
            }
            case E_DISPLAY_BINARY_COLOR_GREEN:
            {
                digit_number = i*2;
            }
        }

        while(ch423_setDigit(E_DISPLAY_BINARY, digit_number, 0) != 0)
        {
            osDelay(1);
        }
    }
}


void display_decimal(S_DISPLAY_NUMBER num)
{
    char dig[12] = {0};

    snprintf(dig, 12, "%ld", num.number);
    for(int8_t i=0 ; i < 12 ; i++)
    {
        dig[i] -= 0x30; // ASCII to Number
    }

    for(int8_t i=0 ; i < 12 ; i++)
    {
        while(ch423_setDigit(E_DISPLAY_DECIMAL, i, display_convertToDigit(dig[i])) != 0)
        {
            osDelay(1);
        }
    }
}


void display_hexa(S_DISPLAY_NUMBER num)
{
    char dig[8] = {0};
    uint8_t digit_number;

    snprintf(dig, 8, "%lX", num.number);
    for(int8_t i=0 ; i < 8 ; i++)
    {
        dig[i] -= 0x30; // ASCII to Number
    }

    for(int8_t i=0 ; i < 4 ; i++)
    {
        if(num.lsb)
        {
            digit_number = 3 - i;
        }
        else
        {
            digit_number = i;
        }

        while(ch423_setDigit(E_DISPLAY_HEXA, (digit_number*2), display_convertToDigit(dig[(i*2)])) != 0)
        {
            osDelay(1);
        }

        while(ch423_setDigit(E_DISPLAY_HEXA, (digit_number*2)+1, display_convertToDigit(dig[(i*2)+1])) != 0)
        {
            osDelay(1);
        }
    }
}


uint8_t display_convertToDigit(char num)
{
    S_DIGIT dig;

    dig.a=0; dig.b=0; dig.c=0; dig.d=0; dig.e=0; dig.f=0; dig.g=0;

    switch(num)
    {
        case '0': dig.a=1; dig.b=1; dig.c=1; dig.d=1; dig.e=1; dig.f=1; dig.g=0; break;
        case '1': dig.a=0; dig.b=1; dig.c=1; dig.d=0; dig.e=0; dig.f=0; dig.g=0; break;
        case '2': dig.a=1; dig.b=1; dig.c=0; dig.d=1; dig.e=1; dig.f=0; dig.g=1; break;
        case '3': dig.a=1; dig.b=1; dig.c=1; dig.d=1; dig.e=0; dig.f=0; dig.g=1; break;
        case '4': dig.a=0; dig.b=1; dig.c=1; dig.d=0; dig.e=0; dig.f=1; dig.g=1; break;
        case '5': dig.a=1; dig.b=0; dig.c=1; dig.d=1; dig.e=0; dig.f=1; dig.g=1; break;
        case '6': dig.a=1; dig.b=0; dig.c=1; dig.d=1; dig.e=1; dig.f=1; dig.g=1; break;
        case '7': dig.a=1; dig.b=1; dig.c=1; dig.d=0; dig.e=0; dig.f=0; dig.g=0; break;
        case '8': dig.a=1; dig.b=1; dig.c=1; dig.d=1; dig.e=1; dig.f=1; dig.g=1; break;
        case '9': dig.a=1; dig.b=1; dig.c=1; dig.d=1; dig.e=0; dig.f=1; dig.g=1; break;
        case 'a':
        case 'A': dig.a=1; dig.b=1; dig.c=1; dig.d=0; dig.e=1; dig.f=1; dig.g=1; break;
        case 'b':
        case 'B': dig.a=0; dig.b=0; dig.c=1; dig.d=1; dig.e=1; dig.f=1; dig.g=1; break;
        case 'c':
        case 'C': dig.a=0; dig.b=0; dig.c=0; dig.d=1; dig.e=1; dig.f=0; dig.g=1; break;
        case 'd':
        case 'D': dig.a=0; dig.b=1; dig.c=1; dig.d=1; dig.e=1; dig.f=0; dig.g=1; break;
        case 'e':
        case 'E': dig.a=1; dig.b=0; dig.c=0; dig.d=1; dig.e=1; dig.f=1; dig.g=1; break;
        case 'f':
        case 'F': dig.a=1; dig.b=0; dig.c=0; dig.d=0; dig.e=1; dig.f=1; dig.g=1; break;

        case '-': dig.a=0; dig.b=0; dig.c=0; dig.d=0; dig.e=0; dig.f=0; dig.g=1; break;
    }

    return dig.value;
}
