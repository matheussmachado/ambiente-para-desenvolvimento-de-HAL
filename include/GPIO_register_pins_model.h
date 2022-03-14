#ifndef GPIO_REGISTER_PINS_H
#define GPIO_REGISTER_PINS_H

#include "../include/convert_pins_to_bits.h"

typedef struct {
  volatile void* register_pointer;
  unsigned char pins; //(o tipo/tamanho vai variar de acordo com o MCU)
} GPIORegisterPins;

// MACROS PARA MAPEAR IOs NA IMPLEMENTAÇÃO DA HAL ATRAVÉS DE UM VETOR
#define PINS (unsigned int[])
#define MAP_IO(devices_pin_mapper, device_id, register_address, pins_vect) ({\
  unsigned int n_pins = sizeof(pins_vect)/sizeof(pins_vect[0]);\
  unsigned int pins = convert_pins_to_bits(n_pins, pins_vect);\
  devices_pin_mapper[device_id] = (GPIORegisterPins) {register_address, pins};\
})

#endif