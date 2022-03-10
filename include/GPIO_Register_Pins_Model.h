#include "../include/hal.h"
#include "../include/convert_pins_to_bits.h"

#define NUM_OUTPUT_DEVICES END_OUTPUT_DEVICES
#define NUM_INPUT_DEVICES END_INPUT_DEVICES
#define PINS (unsigned int[]) // para a passagem de vários pinos através de array. ex: PINS{PIN0, PIN1, PIN2}

typedef struct {
  volatile void* register_pointer;
  unsigned int pins; //binário que representa os bits de um registrador
} GPIO_Register_Pins;

typedef GPIO_Register_Pins output_devices_pins_mapper[NUM_OUTPUT_DEVICES];
typedef GPIO_Register_Pins input_devices_pins_mapper[NUM_INPUT_DEVICES];


#define MAP_IO(devices_pin_mapper, device_id, register_address, pins_vect) ({\
  unsigned int n_pins = sizeof(pins_vect)/sizeof(pins_vect[0]);\
  unsigned int pins = convert_pins_to_bits(n_pins, pins_vect);\
  devices_pin_mapper[device_id] = (GPIO_Register_Pins) {register_address, pins};\
})
