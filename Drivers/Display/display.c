/*
 * display.c
 *
 *  Created on: 22 sept. 2020
 *      Author: steven
 */
#include "stdio.h"
#include "display.h"
#include "ch423.h"





void display_binary(uint32_t num);
void display_decimal(uint32_t num);
void display_hexa(uint32_t num);
void display_mode(S_CALC_MODE mode);
uint8_t convertToDigit(char num);


void display_init()
{
    while(ch423_init() != 0)
    {
        HAL_Delay(1);
    }
}

void display(S_CALC_MODE mode, uint32_t num)
{
    static uint32_t saved_num = 0;
    static uint8_t firstLaunch = 1;

    if(saved_num != num || firstLaunch)
    {
        display_binary(num);
        display_decimal(num);
        display_hexa(num);
        display_mode(mode);

        saved_num = num;
        firstLaunch = 0;
    }
}






void display_binary(uint32_t num)
{
    for(int8_t i=0 ; i < 4 ; i++)
    {
        while(ch423_setDigit(E_DISPLAY_BINARY, i, (num >> i*8) & 0xFF) != 0)
        {
            HAL_Delay(1);
        }
    }
}

void display_decimal(uint32_t num)
{
    char dig[12] = {0};

    snprintf(dig, 12, "%ld", num);

    for(int8_t i=0 ; i < 12 ; i++)
    {
        while(ch423_setDigit(E_DISPLAY_HEXA, i, convertToDigit(dig[i])) != 0)
        {
            HAL_Delay(1);
        }
    }
}

void display_hexa(uint32_t num)
{
    char dig[8] = {0};

    snprintf(dig, 8, "%lX", num);

    for(int8_t i=0 ; i < 8 ; i++)
    {
        while(ch423_setDigit(E_DISPLAY_HEXA, i, convertToDigit(dig[i])) != 0)
        {
            HAL_Delay(1);
        }
    }
}

void display_mode(S_CALC_MODE mode)
{
    if(mode.mode == E_SELECT_MODE_BIN)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
    }

    if(mode.mode == E_SELECT_MODE_DEC)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
    }

    if(mode.mode == E_SELECT_MODE_HEX)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
    }

    if(mode.mode == E_SELECT_MODE_LSD)
    {
        HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
    }
    else
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
    }
}

uint8_t convertToDigit(char num)
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
