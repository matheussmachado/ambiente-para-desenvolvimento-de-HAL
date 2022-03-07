/* INTERFACE PARA UMA HAL EXTERNA:
 * 
 * ESTA INTERFACE DETERMINA O QUE DEVERÁ SER IMPLEMENTADO POR UMA HAL EXTERNA
 * ESTA INTERFACE ESTÁ EXPONDO OS REQUISITOS DA APLICAÇÃO
 */

// DEFINIÇÃO DOS DISPOSITIVOS A SEREM MAPEADOS NA IMPLEMENTAÇÃO DA HAL EXTERNA
//==============================================================================
#ifndef HAL_H
#define HAL_H

typedef enum output_devices_identifiers {
  LED_A, LED_B, LED_C, LED_D, LED_E, LED_F, END_OUTPUT_DEVICES
} out_id;

typedef enum input_devices_identifiers {
  PUSH_BUTTON_A, PUSH_BUTTON_B, PUSH_BUTTON_C, END_INPUT_DEVICES
} in_id;
//==============================================================================

// DEFINIÇÃO DOS PROTOCOLOS A SEREM IMPLEMENTADOS PELA HAL EXTERNA
//==============================================================================
void set_output_Service(out_id id);
void clear_output_Service(out_id id);
void flip_output_Service(out_id id);
int test_input_Service(in_id id);
void setup_hardware_Service(void);
void one_sec_interrupt_Service(void *routine);
void push_button_A_interrupt_Service(void *routine);
void push_button_B_interrupt_Service(void *routine);
//==============================================================================
#endif