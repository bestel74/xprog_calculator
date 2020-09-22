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
    init.bit.INTENS = E_CH423_INTENS_LOW;
    init.bit.SLEEP = 0;

    status = HAL_I2C_Master_Transmit_DMA(&hi2c1, CH423_REG_ADDR_CTRL, &init.value, 1);
    status |= HAL_I2C_Master_Transmit_DMA(&hi2c2, CH423_REG_ADDR_CTRL, &init.value, 1);
    status |= HAL_I2C_Master_Transmit_DMA(&hi2c3, CH423_REG_ADDR_CTRL, &init.value, 1);

    if(status == HAL_OK)
    {
        return 0;
    }

    return -1;
}


int ch423_setDigit(E_DISPLAY display, uint8_t digit_number, uint8_t digit_value)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    switch(display)
    {
        case E_DISPLAY_BINARY:
        {
            status = HAL_I2C_Master_Transmit_DMA(&hi2c1, CH423_REG_ADDR_DIG0 + (digit_number<<1), &digit_value, 1);
            break;
        }

        case E_DISPLAY_DECIMAL:
        {
            status = HAL_I2C_Master_Transmit_DMA(&hi2c2, CH423_REG_ADDR_DIG0 + (digit_number<<1), &digit_value, 1);
            break;
        }

        case E_DISPLAY_HEXA:
        {
            status = HAL_I2C_Master_Transmit_DMA(&hi2c3, CH423_REG_ADDR_DIG0 + (digit_number<<1), &digit_value, 1);
            break;
        }
    }

    if(status == HAL_OK)
    {
        return 0;
    }

    return -1;
}
