/*
 * ch423.h
 *
 *  Created on: 22 sept. 2020
 *      Author: steven
 */

#ifndef CH423_CH423_H_
#define CH423_CH423_H_

#include "stm32f4xx.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;


// Defines
#define     CH423_REG_ADDR_CTRL        0x48
#define     CH423_REG_ADDR_DIG0        0x60

typedef enum
{
    E_CH423_INTENS_HIGH    =   0,
    E_CH423_INTENS_LOW     =   1,
    E_CH423_INTENS_MED     =   2,
    // E_CH423_INTENS_FULL     =   3,  // No current overload protected
} E_CH423_INTENS;


typedef enum
{
    E_DISPLAY_BINARY,
    E_DISPLAY_DECIMAL,
    E_DISPLAY_HEXA,
} E_DISPLAY;



// Registers
typedef struct
{
    union
    {
        struct
        {
            uint8_t IO_OE: 1;     // Input/Output 'output' enable
            uint8_t DEC_L: 1;     // 0C0~0C7 dynamic scan (multiplexing)
            uint8_t DEC_H: 1;     // 0C8~0C15 dynamic scan (multiplexing)
            uint8_t X_INT: 1;     // Interrupt enable
            uint8_t OD_EN: 1;     // 0C0~0C15 Open drain
            uint8_t INTENS: 2;    // 00B, 01B, 10B, 11B = PWM 4/4, 1/4, 2/4, 4/4 without current protection
            uint8_t SLEEP: 1;     // Low power state
        } bit;
        uint8_t value;
    };
} S_CH423_CTRL;





int ch423_init();
int ch423_setDigit(E_DISPLAY display, uint8_t digit_number, uint8_t digit_value);



#endif /* CH423_CH423_H_ */
