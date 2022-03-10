#include "../include/main.h"

unsigned char max_timer1, max_timer2, max_timer3;

int main(void) {
  setup_hardware_Service();
  one_sec_interrupt_Service(f_one_sec_timer);
  one_milisec_interrupt_Service(f_one_milisec_timer);
  push_button_B_interrupt_Service(control_LED_D);
  push_button_A_interrupt_Service(control_LED_E);
  push_button_F_interrupt_Service(control_LED_BLOCK);
  setup_variables();
  while(1) continue;
  return 0;
}

void setup_variables(void) {
  max_timer1 = 1,
  max_timer2 = 2,  
  max_timer3 = 4;
}

void f_one_milisec_timer(void) {
  #define PIN_PUSH_BUTTON_D 0b01000000
  #define PIN_PUSH_BUTTON_E 0b10000000
  static int read = 0;
  read = read_inputs_Service(PUSH_BUTTON_BLOCK);
  switch (read) {
  case PIN_PUSH_BUTTON_D:  
    set_outputs_Service(LED_F);
    clear_outputs_Service(LED_G);
    clear_outputs_Service(LED_H);
    break;
  case PIN_PUSH_BUTTON_E:
    set_outputs_Service(LED_H);
    clear_outputs_Service(LED_F);
    clear_outputs_Service(LED_G);
    break;
  case (PIN_PUSH_BUTTON_D | PIN_PUSH_BUTTON_E):
    set_outputs_Service(LED_G);
    clear_outputs_Service(LED_F);
    clear_outputs_Service(LED_H);
    break;
  default: 
    clear_outputs_Service(LED_F);
    clear_outputs_Service(LED_G);
    clear_outputs_Service(LED_H);
    break;
  }  
}

void f_one_sec_timer(void) {  
  static unsigned char c_timer1 = 1;
  static unsigned char c_timer2 = 1;
  static unsigned char c_timer3 = 1;
  if(c_timer1 < max_timer1) c_timer1++;
  else {
    f_timer1();
    c_timer1 = 1;
  }
  if (c_timer2 < max_timer2) c_timer2++;
  else {
    f_timer2();
    c_timer2 = 1;
  }
  if(c_timer3 < max_timer3) c_timer3++;
  else {
    f_timer3();
    c_timer3 = 1;
  }
}

void f_timer1(void) {
  flip_outputs_Service(LED_A);
}

void f_timer2(void) {
  flip_outputs_Service(LED_B);
}

void f_timer3(void) {
  flip_outputs_Service(LED_C);
}

void control_LED_D(void) {
  control_output_via_input_trigger(PUSH_BUTTON_A, LED_D);
}

void control_LED_E(void) {
  control_output_via_input_trigger(PUSH_BUTTON_B, LED_E);
}

void control_LED_BLOCK(void) {
  control_output_via_input_trigger(PUSH_BUTTON_C, LED_BLOCK);
}
