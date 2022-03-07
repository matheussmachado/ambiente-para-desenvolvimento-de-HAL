#include "../include/hal.h"

#define NUM_OUTPUT_DEVICES END_OUTPUT_DEVICES
#define NUM_INPUT_DEVICES END_INPUT_DEVICES

typedef struct {
  volatile void* register_pointer;
  unsigned int pins; //binário que representa os bits de um registrador
} GPIO_register_pins;

typedef GPIO_register_pins output_devices_pins_mapper[NUM_OUTPUT_DEVICES];
typedef GPIO_register_pins input_devices_pins_mapper[NUM_INPUT_DEVICES];


#define MAP_IO(devices_pin_mapper, device_id, register_address, pins) ({\
  devices_pin_mapper[device_id] = (GPIO_register_pins) {register_address, pins};\
})
