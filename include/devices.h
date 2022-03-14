#ifndef DEVICES_H
#define DEVICES_H
/*  DEFINIÇÃO DOS DISPOSITIVOS, USADOS NA APLICAÇÃO, A SEREM MAPEADOS NA 
    IMPLEMENTAÇÃO DA HAL EXTERNA */
//==============================================================================
typedef enum OutputDevicesIdentifiers {
  LED_A, LED_B, LED_C, LED_D, LED_E, LED_F, LED_G, LED_BLOCK_A, LED_BLOCK_B,  END_OUTPUT_DEVICES
} out_id;

typedef enum InputDevicesIdentifiers {
  PUSH_BUTTON_A, PUSH_BUTTON_B, PUSH_BUTTON_C, PUSH_BUTTON_D, PUSH_BUTTON_E, PUSH_BUTTON_BLOCK, END_INPUT_DEVICES
} in_id;

#define NUM_OUTPUT_DEVICES END_OUTPUT_DEVICES
#define NUM_INPUT_DEVICES END_INPUT_DEVICES
//==============================================================================
#endif