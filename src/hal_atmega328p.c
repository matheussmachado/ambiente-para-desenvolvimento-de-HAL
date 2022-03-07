/* IMPLEMENTAÇÃO DE UMA HAL PARA O ATMEGA328P, OBEDECENDO A INTERFACE EXPOSTA EM hal.h */

#include "../include/hal.h"
#include "../include/GPIO_Register_Pins_Model.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// MAPEAMENTO DOS DISPOSITIVOS EM PINOS DE I/O E SETUP
//==============================================================================
output_devices_pins_mapper out_mp;
input_devices_pins_mapper in_mp;

void setup_output_devices_pins_mapper(void) {
  MAP_IO(out_mp, LED_A, &PORTB, PB1);
  MAP_IO(out_mp, LED_B, &PORTB, PB2);
  MAP_IO(out_mp, LED_C, &PORTB, PB3);
  MAP_IO(out_mp, LED_D, &PORTB, PB4);
  MAP_IO(out_mp, LED_E, &PORTB, PB5);
  MAP_IO(out_mp, LED_F, &PORTB, PB0);
}

void setup_input_devices_pins_mapper(void) {
  MAP_IO(in_mp, PUSH_BUTTON_A, &PINC, PC0);
  MAP_IO(in_mp, PUSH_BUTTON_B, &PINC, PC1);
}

void setup_hardware_Service(void) {
  // GPIOS
  DDRB = 0b00111111;
  PORTB = 0b11000000;
  DDRC = 0x00;
  PORTC = 0b00000011;
  DDRD = 0xFF;

  // INTERRUPÇÃO TIMER
  TCCR1B = 0b00000101;
  TIMSK1 = 0b00000001;
  TCNT1 = 49911; //inicio da contagem para overflow em 1 seg.

  // INTERRUPÇÃO EXTERNA
  PCICR = 0b00000011;
  PCMSK0 = 0b11000000;
  PCMSK1 = 0b00000011;

  setup_output_devices_pins_mapper();
  setup_input_devices_pins_mapper();
  sei();
}
//==============================================================================

// ACESSO À BITS
//==============================================================================
__attribute((always_inline)) inline void set_output_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) |= (1 << out_mp[id].pins);
}

__attribute((always_inline)) inline void clear_output_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) &= ~(1 << out_mp[id].pins);  
}

__attribute((always_inline)) inline void flip_output_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) ^= (1 << out_mp[id].pins);  
}

__attribute((always_inline)) inline int test_input_Service(in_id id) {
  return (!(*(uint8_t*)(in_mp[id].register_pointer) & (1 << in_mp[id].pins)));
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
  pin_change_interrupt_routine2();
}

//==============================================================================