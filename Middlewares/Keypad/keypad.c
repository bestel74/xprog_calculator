/*
 * keypad.c
 *
 *  Created on: 23 sept. 2020
 *      Author: steven
 */
#include "keypad.h"
#include "string.h"
#include "stm32f4xx.h"

#include "keypad_map.h"


extern TIM_HandleTypeDef htim3;


osThreadId keypadTaskHandle;
osPoolDef(mpool_keypad, 16, S_KEYPAD_MSG);
osPoolId  mpool_keypad;
osMessageQDef(msgbox_keypad, 16, S_KEYPAD_MSG*);
osMessageQId  msgbox_keypad;




uint8_t switch_state_new[KEYPAD_OUTPUT_PINS][KEYPAD_INPUT_PINS];
uint8_t switch_state_prev[KEYPAD_OUTPUT_PINS][KEYPAD_INPUT_PINS];



void keypad_scan();




void keypad_Task_create()
{
    osThreadDef(keypadTask, keypad_Task_entry, osPriorityHigh, 0, 512);
    keypadTaskHandle = osThreadCreate(osThread(keypadTask), NULL);

    keypad_init();

    HAL_TIM_Base_Start_IT(&htim3);
}


void keypad_Task_entry(void const * argument)
{
  /* USER CODE BEGIN keypadTask_entry */
    osEvent  evt;
    S_KEYPAD_MSG *msg;

    /* Infinite loop */
     for(;;)
     {
         evt = osMessageGet(msgbox_keypad, osWaitForever);  // wait for message
         if (evt.status == osEventMessage) {
             msg = evt.value.p;
             switch(msg->msgid)
             {
                 case E_KEYPAD_MSG_ID_REFRESH:
                 {
                     keypad_scan();
                     break;
                 }

                 case E_KEYPAD_MSG_ID_KEY_EVENT:
                 {
                     if(msg->data.key_event.event == E_KEYPAD_KEY_EVENT_PRESS)
                     {
                         switch(msg->data.key_event.key)
                         {
                             case E_KEYPAD_KEY_0:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_1:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_2:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_3:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_4:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_5:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_6:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_7:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_8:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_9:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_A:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_B:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_C:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_D:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_E:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_F:
                             {
                                 break;
                             }


                             case E_KEYPAD_KEY_PLUS:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_MINUS:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_MULT:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_DIV:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_EQUAL:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_MODE:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_SETTING:
                             {
                                 break;
                             }

                             case E_KEYPAD_KEY_CLEAR:
                             {
                                 break;
                             }

                         }
                     }
                     break;
                 }
             }

             osPoolFree(mpool_keypad, msg);                  // free memory allocated for message
         }
     }
  /* USER CODE END keypadTask_entry */
}


void keypad_sendMsg(E_KEYPAD_MSG_ID msg_id)
{
    S_KEYPAD_MSG *msg;

    msg = osPoolAlloc(mpool_keypad);
    if(msg)
    {
        msg->msgid = msg_id;
        osMessagePut(msgbox_keypad, (uint32_t)msg, osWaitForever);
    }
}


void keypad_sendEventKey(S_KEYPAD_MSG msg)
{
    S_KEYPAD_MSG *m;

    m = osPoolAlloc(mpool_keypad);
    if(m)
    {
        m->msgid = msg.msgid;
        m->data.key_event = msg.data.key_event;
        osMessagePut(msgbox_keypad, (uint32_t)m, osWaitForever);
    }
}




void keypad_init()
{
    memset(switch_state_new, 0, KEYPAD_OUTPUT_PINS + KEYPAD_INPUT_PINS);
    memset(switch_state_prev, 0, KEYPAD_OUTPUT_PINS + KEYPAD_INPUT_PINS);

    HAL_GPIO_WritePin(keypad_map_output[0].gpio, keypad_map_output[0].pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(keypad_map_output[1].gpio, keypad_map_output[1].pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(keypad_map_output[2].gpio, keypad_map_output[2].pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(keypad_map_output[3].gpio, keypad_map_output[3].pin, GPIO_PIN_RESET);
}


void keypad_scan()
{
    S_KEYPAD_MSG evt;

    // Get new state
    for(uint8_t i=0 ; i < KEYPAD_OUTPUT_PINS ; i++)
    {
        HAL_GPIO_WritePin(keypad_map_output[i].gpio, keypad_map_output[i].pin, GPIO_PIN_SET);

        // Let low-pass filter voltage up
        osDelay(2);

        for(uint8_t j=0 ; j < KEYPAD_INPUT_PINS ; j++)
        {
            switch_state_new[i][j] = HAL_GPIO_ReadPin(keypad_map_input[i].gpio, keypad_map_input[i].pin);
        }

        HAL_GPIO_WritePin(keypad_map_output[i].gpio, keypad_map_output[i].pin, GPIO_PIN_RESET);
    }

    // Compare to previous state to generate UP/DOWN events
    for(uint8_t i=0 ; i < KEYPAD_OUTPUT_PINS ; i++)
    {
        for(uint8_t j=0 ; j < KEYPAD_INPUT_PINS ; j++)
        {
            if(switch_state_prev[i][j] != switch_state_new[i][j])
            {
                evt.msgid = E_KEYPAD_MSG_ID_KEY_EVENT;
                evt.data.key_event.event = switch_state_new[i][j];
                evt.data.key_event.key = keypad_map_convert(&keypad_map_output[i], &keypad_map_input[j]);

                keypad_sendEventKey(evt);
                switch_state_prev[i][j] = switch_state_new[i][j];
            }
        }
    }
}
