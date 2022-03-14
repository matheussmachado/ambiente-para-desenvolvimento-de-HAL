// SIMULAÇÃO DA DEPENDENCIA QUE IMPLEMENTA A HAL
#include <stdint.h>
#include "samples.h"

#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7

uint8_t PINB_Mock;
uint8_t PORTB_Mock;

static void set_output_Service(out_dev_id id) {
  *(uint8_t*)(out_mp_test[id].register_pointer) |= out_mp_test[id].pins;
}

static void clear_outputs_Service(out_dev_id id) {
  *(uint8_t*)(out_mp_test[id].register_pointer) &= ~(out_mp_test[id].pins);
}

static void flip_outputs_Service(out_dev_id id) {
  *(uint8_t*)(out_mp_test[id].register_pointer) ^= out_mp_test[id].pins;
}

static int read_inputs_Service(in_dev_id id) {
  return (*(uint8_t*)(in_mp_test[id].register_pointer) & in_mp_test[id].pins);
}

static unsigned char get_input_pins_Service(in_dev_id device) {
  return (in_mp_test[device].pins);
}