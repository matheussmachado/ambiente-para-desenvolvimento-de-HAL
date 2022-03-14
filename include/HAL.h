#ifndef HAL_H
#define HAL_H

#include "../include/devices.h"

/* INTERFACE PARA UMA HAL EXTERNA:
 * 
 * ESTA INTERFACE DETERMINA O QUE DEVERÁ SER IMPLEMENTADO POR UMA HAL EXTERNA
 * ESTA INTERFACE ESTÁ EXPONDO OS REQUISITOS DA APLICAÇÃO
 */

// DEFINIÇÃO DOS PROTOCOLOS A SEREM IMPLEMENTADOS PELA HAL EXTERNA
//==============================================================================
void setup_hardware_Service(void);
void set_outputs_Service(out_id id);
void clear_outputs_Service(out_id id);
void flip_outputs_Service(out_id id);
char test_input_Service(in_id id); // para dispositivos de apenas 1 pino
int read_inputs_Service(in_id id);
int get_inputs_device_pins_Service(in_id id);
void one_milisec_interrupt_Service(void *routine);
void one_sec_interrupt_Service(void *routine);
void push_button_A_interrupt_Service(void *routine);
void push_button_B_interrupt_Service(void *routine);
void push_button_F_interrupt_Service(void *routine);
//==============================================================================
#endif