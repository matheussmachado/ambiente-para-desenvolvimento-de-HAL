#include "../include/hal.h"

unsigned char max_timer1, max_timer2, max_timer3;


void f_timer1(void) {
  flip_output_Service(LED_B);
}

void f_timer2(void) {
  flip_output_Service(LED_C);
}

void f_timer3(void) {
  flip_output_Service(LED_D);
}

void f_timers(void) {
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

void control_led_A(void) {
  static int button_pressed = 0;
  button_pressed = test_input_Service(PUSH_BUTTON_A);
  if (button_pressed) {
    set_output_Service(LED_A);
    return;
  }
  clear_output_Service(LED_A);
}

void control_led_E(void) {
  static int button_pressed2 = 0;
  button_pressed2 = test_input_Service(PUSH_BUTTON_B);
  if (button_pressed2) {
    set_output_Service(LED_E);
    return;
  }
  clear_output_Service(LED_E);
}

void setup_variables(void) {
  max_timer1 = 1,
  max_timer2 = 2,  
  max_timer3 = 4;
}

int main(void) {
  setup_hardware_Service();
  one_sec_interrupt_Service(f_timers);
  push_button_A_interrupt_Service(control_led_A);
  push_button_B_interrupt_Service(control_led_E);
  setup_variables();
  while(1) continue;
  return 0;
}
