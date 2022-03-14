#include "../include/gpio_circuit_1.h"
#include "../include/HAL.h"
#define INPUT(device) (get_inputs_device_pins_Service(device))

unsigned char max_timer1, max_timer2, max_timer3;

void f_timer1(void);
void f_timer2(void);
void f_timer3(void);
void f_one_sec_timer(void);
void f_one_milisec_timer(void);
void control_LED_D(void);
void control_LED_E(void);
void control_LED_BLOCK_A(void);
void setup_variables(void);


void setup(void) {
  setup_hardware_Service();
  one_sec_interrupt_Service(f_one_sec_timer);
  one_milisec_interrupt_Service(f_one_milisec_timer);
  push_button_B_interrupt_Service(control_LED_D);
  push_button_A_interrupt_Service(control_LED_E);
  push_button_F_interrupt_Service(control_LED_BLOCK_A);
  setup_variables();
}

void control_output_via_input_trigger(in_id input ,out_id output) {
  unsigned char input_triggered = 0;
  input_triggered = test_input_Service(input);
  if (input_triggered) {
    set_outputs_Service(output);
    return;
  }
  clear_outputs_Service(output);
}

void setup_variables(void) {
  max_timer1 = 1,
  max_timer2 = 2,  
  max_timer3 = 4;
}

void f_one_milisec_timer(void) {
  static int read = 0;
  read = read_inputs_Service(PUSH_BUTTON_BLOCK);
  if (read == INPUT(PUSH_BUTTON_D)) {
    set_outputs_Service(LED_F);
    clear_outputs_Service(LED_G);
  } else if (read == INPUT(PUSH_BUTTON_E)) {
    set_outputs_Service(LED_G);
    clear_outputs_Service(LED_F);
  } else if (read == INPUT(PUSH_BUTTON_BLOCK)) {
    set_outputs_Service(LED_BLOCK_B);
  } else {
    clear_outputs_Service(LED_BLOCK_B);
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

void control_LED_BLOCK_A(void) {
  control_output_via_input_trigger(PUSH_BUTTON_C, LED_BLOCK_A);
}
