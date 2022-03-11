#include "../include/HAL.h"

void control_output_via_input_trigger(in_id input ,out_id output) {
  unsigned char input_triggered = 0;
  input_triggered = test_input_Service(input);
  if (input_triggered) {
    set_outputs_Service(output);
    return;
  }
  clear_outputs_Service(output);
}

void f_timer1(void);
void f_timer2(void);
void f_timer3(void);
void f_one_sec_timer(void);
void f_one_milisec_timer(void);
void control_LED_D(void);
void control_LED_E(void);
void control_LED_BLOCK_A(void);
void setup_variables(void);
