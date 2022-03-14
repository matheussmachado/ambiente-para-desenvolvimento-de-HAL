/* IMPLEMENTAÇÃO DE UMA HAL PARA O ATMEGA328P, OBEDECENDO A INTERFACE EXPOSTA EM HAL.h */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/HAL.h"
#include "../include/GPIO_register_pins_model.h"

// MAPEAMENTO DOS DISPOSITIVOS EM PINOS DE I/O E SETUP
//==============================================================================
typedef GPIORegisterPins output_devices_pins_mapper[NUM_OUTPUT_DEVICES];
typedef GPIORegisterPins input_devices_pins_mapper[NUM_INPUT_DEVICES];

output_devices_pins_mapper out_mp;
input_devices_pins_mapper in_mp;

void setup_output_devices_pins_mapper(void) {
  MAP_IO(out_mp, LED_A, &PORTB, (PINS{PB2}));
  MAP_IO(out_mp, LED_B, &PORTB, (PINS{PB3}));
  MAP_IO(out_mp, LED_C, &PORTB, (PINS{PB4}));
  MAP_IO(out_mp, LED_D, &PORTC, (PINS{PC2}));
  MAP_IO(out_mp, LED_E, &PORTC, (PINS{PC3}));
  MAP_IO(out_mp, LED_F, &PORTB, (PINS{PB0}));
  MAP_IO(out_mp, LED_G, &PORTB, (PINS{PB1}));
  MAP_IO(out_mp, LED_BLOCK_B, &PORTB, (PINS{PB0, PB1}));
  MAP_IO(out_mp, LED_BLOCK_A, &PORTD, (PINS{PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7}));
}

void setup_input_devices_pins_mapper(void) {
  MAP_IO(in_mp, PUSH_BUTTON_A, &PINC, (PINS{PC4}));
  MAP_IO(in_mp, PUSH_BUTTON_B, &PINC, (PINS{PC5}));
  MAP_IO(in_mp, PUSH_BUTTON_C, &PINC, (PINS{PC6}));
  MAP_IO(in_mp, PUSH_BUTTON_D, &PINB, (PINS{PB6}));
  MAP_IO(in_mp, PUSH_BUTTON_E, &PINB, (PINS{PB7}));
  MAP_IO(in_mp, PUSH_BUTTON_BLOCK, &PINB, (PINS{PB6, PB7}));
}

void setup_hardware_Service(void) {
  // GPIOs
  DDRB = 0b00111111;
  PORTB = 0b00000000;
  DDRC = 0b00001100;
  PORTC = 0b01110000;
  DDRD = 0xFF;

  //INTERRUPÇÃO TIMER 0: 8 bits
  TCCR0B = 0b00000100;
  TIMSK0 = 0b00000001;
  TCNT0 = 194; // inicio da contagem para ovf em 1 ms

  // INTERRUPÇÃO TIMER 1: 16 bits
  TCCR1B = 0b00000101;
  TIMSK1 = 0b00000001;
  TCNT1 = 49911; //inicio da contagem para overflow em 1 seg.

  // INTERRUPÇÃO EXTERNA
  PCICR = 0b00000010;
  PCMSK1 = 0b01110000;

  setup_output_devices_pins_mapper();
  setup_input_devices_pins_mapper();
  sei();
}
//==============================================================================

// ACESSO À BITS
//==============================================================================
__attribute((always_inline)) inline void set_outputs_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) |= out_mp[id].pins;
}

__attribute((always_inline)) inline void clear_outputs_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) &= ~(out_mp[id].pins);
}

__attribute((always_inline)) inline void flip_outputs_Service(out_id id) {
  *(uint8_t*)(out_mp[id].register_pointer) ^= out_mp[id].pins;
}

__attribute((always_inline)) inline char test_input_Service(in_id id) {
  return (!(*(uint8_t*)(in_mp[id].register_pointer) & in_mp[id].pins));
}

__attribute((always_inline)) inline int read_inputs_Service(in_id id) {
  return (*(uint8_t*)(in_mp[id].register_pointer) & in_mp[id].pins);
}

__attribute((always_inline)) inline int get_inputs_device_pins_Service(in_id id) {
  return (in_mp[id].pins);
}
//==============================================================================

// INTERRUPÇÕES
//==============================================================================
typedef void (*interrupt_routine)(void);

static interrupt_routine one_sec_interrupt_routine;
static interrupt_routine one_milisec_interrupt_routine;
static interrupt_routine pin_change_interrupt_routine;
static interrupt_routine pin_change_interrupt_routine2;
static interrupt_routine pin_change_interrupt_routine3;

//--------------------- interfaces -----------------------
void one_milisec_interrupt_Service(void *routine) {
  one_milisec_interrupt_routine = (interrupt_routine) routine;
}

void one_sec_interrupt_Service(void *routine) {
  one_sec_interrupt_routine = (interrupt_routine) routine;
}

void push_button_A_interrupt_Service(void *routine) {
  pin_change_interrupt_routine = (interrupt_routine) routine;
}

void push_button_B_interrupt_Service(void *routine) {
  pin_change_interrupt_routine2 = (interrupt_routine) routine;
}

void push_button_F_interrupt_Service(void *routine) {
  pin_change_interrupt_routine3 = (interrupt_routine) routine;
}
//--------------------------------------------------------

ISR(TIMER0_OVF_vect) {
  TCNT0 = 194;
  one_milisec_interrupt_routine();
}

ISR(TIMER1_OVF_vect) {    
  TCNT1 = 49911;
  one_sec_interrupt_routine();
}

ISR(PCINT1_vect) {
  pin_change_interrupt_routine();
  pin_change_interrupt_routine2();
  pin_change_interrupt_routine3();
}

//==============================================================================