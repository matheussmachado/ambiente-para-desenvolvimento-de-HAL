#include "../include/GPIO_register_pins_model.h"

typedef enum output_devices_ids {
  LED_XA, LED_XB, DISPLAY_SEVEN, FOUR_BAR_LED, END_OUTPUT_DEV_TEST
} out_dev_id;

typedef enum input_devices_ids {
  SIDE_SENSORS, RIGHT_SNSR, LEFT_SNSR, FRONTAL_SENSORS, FRONTAL_SNSRS_0_1, FRONTAL_SNSRS_1_2, FRONTAL_SNSRS_2_3, FRONTAL_SNSRS_3_4, END_INPUT_DEV_TEST
} in_dev_id;

typedef GPIORegisterPins output_devices_pins_mapper[END_OUTPUT_DEV_TEST];
typedef GPIORegisterPins input_devices_pins_mapper[END_INPUT_DEV_TEST];

output_devices_pins_mapper out_mp_test;
output_devices_pins_mapper in_mp_test;
