#include "../include/hal.h"

#define NUM_OUTPUT_DEVICES END_OUTPUT_DEVICES
#define NUM_INPUT_DEVICES END_INPUT_DEVICES

typedef struct {
  volatile void* register_pointer;
  int pin;
} GPIO_Pin_Register;

typedef GPIO_Pin_Register output_devices_pin_mapper[NUM_OUTPUT_DEVICES];
typedef GPIO_Pin_Register input_devices_pin_mapper[NUM_INPUT_DEVICES];


#define MAP_IO(devices_pin_mapper, device_id, register_address, pin) ({\
  devices_pin_mapper[device_id] = (GPIO_Pin_Register) {register_address, pin};\
})
