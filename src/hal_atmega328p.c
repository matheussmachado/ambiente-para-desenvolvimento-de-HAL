/* IMPLEMENTAÇÃO DE UMA HAL PARA O ATMEGA328P, OBEDECENDO A INTERFACE EXPOSTA EM hal.h */


#include "../include/hal.h"
#include "../include/GPIO_Pin_Register_Model.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// MAPEAMENTO DOS DISPOSITIVOS EM PINOS DE I/O E SETUP
//==============================================================================
output_devices_pin_mapper out_mp;
input_devices_pin_mapper in_mp;

void setup_output_devices_pin_mapper(void) {
  MAP_IO(out_mp, LED_A, &PORTB, PB0);
  MAP_IO(out_mp, LED_B, &PORTB, PB1);
  MAP_IO(out_mp, LED_C, &PORTB, PB2);
  MAP_IO(out_mp, LED_D, &PORTB, PB3);
  MAP_IO(out_mp, LED_E, &PORTB, PB4);
}

void setup_input_devices_pin_mapper(void) {
  MAP_IO(in_mp, PUSH_BUTTON_A, &PINC, PC6);
  MAP_IO(in_mp, PUSH_BUTTON_B, &PIND, PD6);
}

void setup_hardware_Service(void) {
  // LEDS
  DDRB = 0xFF;

  // PUSH BUTTONS
  DDRC = 0x00;
  PORTC = 0b01000000;
  DDRD = 0x00;
  PORTD = 0b01000000;

  // INTERRUPÇÃO TIMER
  TCCR1B = 0b00000101;
  TIMSK1 = 0b00000001;
  TCNT1 = 49911; //inicio da contagem para overflow em 1 seg.

  // INTERRUPÇÃO EXTERNA
  PCICR = 0b00000110;
  PCMSK1 = 0b01000000;
  PCMSK2 = 0b01000000;

  setup_output_devices_pin_mapper();
  setup_input_devices_pin_mapper();
  sei();
}
//==============================================================================

// ACESSO À BITS
//==============================================================================
__attribute((always_inline)) inline void set_output_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) |= (1 << out_mp[id].pin);
}

__attribute((always_inline)) inline void clear_output_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) &= ~(1 << out_mp[id].pin);  
}

__attribute((always_inline)) inline void flip_output_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) ^= (1 << out_mp[id].pin);  
}

__attribute((always_inline)) inline int test_input_Service(in_id id) {
  return (!(*(uint8_t*)(in_mp[id].register_pointer) & (1 << in_mp[id].pin)));
}
//==============================================================================

// INTERRUPÇÕES
//==============================================================================
typedef void (*interrupt_routine)(void);

static interrupt_routine one_sec_interrupt_routine;
static interrupt_routine pin_change_interrupt_routine;
static interrupt_routine pin_change_interrupt_routine2;

//--------------------- interfaces -----------------------
void one_sec_interrupt_Service(void *routine) {
  one_sec_interrupt_routine = (interrupt_routine) routine;
}

void push_button_A_interrupt_Service(void *routine) {
  pin_change_interrupt_routine = (interrupt_routine) routine;
}

void push_button_B_interrupt_Service(void *routine) {
  pin_change_interrupt_routine2 = (interrupt_routine) routine;
}
//--------------------------------------------------------

ISR(TIMER1_OVF_vect) {    
  TCNT1 = 49911;
  one_sec_interrupt_routine();
}

ISR(PCINT1_vect) {
  pin_change_interrupt_routine();
}

ISR(PCINT2_vect) {
  pin_change_interrupt_routine2();
}

//==============================================================================