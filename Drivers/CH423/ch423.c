/*
 * ch423.c
 *
 *  Created on: 22 sept. 2020
 *      Author: steven
 */
#include "ch423.h"



int ch423_init()
{
    HAL_StatusTypeDef status;
    S_CH423_CTRL init;

    init.bit.IO_OE = 1;
    init.bit.DEC_L = 1;
    init.bit.DEC_H = 1;
    init.bit.X_INT = 0;
    init.bit.OD_EN = 1;
    init.bit.SLEEP = 0;

    init.bit.INTENS = E_CH423_INTENS_LOW;
    status = HAL_I2C_Master_Transmit(&hi2c1, CH423_REG_ADDR_CTRL, &init.value, 1, 10);

    init.bit.INTENS = E_CH423_INTENS_MED;
    status |= HAL_I2C_Master_Transmit(&hi2c2, CH423_REG_ADDR_CTRL, &init.value, 1, 10);
    status |= HAL_I2C_Master_Transmit(&hi2c3, CH423_REG_ADDR_CTRL, &init.value, 1, 10);

    if(status == HAL_OK)
    {
        return 0;
    }

    return -1;
}


int ch423_setDigit(E_DISPLAY display, uint8_t digit_number, uint8_t digit_value)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    // Fix: Digit order is inversed on each display
#if defined(FIX_V1)
    if(display == E_DISPLAY_DECIMAL || display == E_DISPLAY_HEXA)
    {
        if(digit_number == 0 || digit_number == 4 || digit_number == 8)
        {
            digit_number += 3;
        }
        else if(digit_number == 1 || digit_number == 5 || digit_number == 9)
        {
            digit_number += 1;
        }
        else if(digit_number == 2 || digit_number == 6 || digit_number == 10)
        {
            digit_number -= 1;
        }
        else if(digit_number == 3 || digit_number == 7 || digit_number == 11)
        {
            digit_number -= 3;
        }
    }
#endif

    switch(display)
    {
        case E_DISPLAY_BINARY:
        {
            status = HAL_I2C_Master_Transmit(&hi2c1, CH423_REG_ADDR_DIG0 + (digit_number<<1), &digit_value, 1, 10);
            break;
        }

        case E_DISPLAY_DECIMAL:
        {
            status = HAL_I2C_Master_Transmit(&hi2c2, CH423_REG_ADDR_DIG0 + (digit_number<<1), &digit_value, 1, 10);
            break;
        }

        case E_DISPLAY_HEXA:
        {
            status = HAL_I2C_Master_Transmit(&hi2c3, CH423_REG_ADDR_DIG0 + (digit_number<<1), &digit_value, 1, 10);
            break;
        }
    }

    if(status == HAL_OK)
    {
        return 0;
    }

    return -1;
}
