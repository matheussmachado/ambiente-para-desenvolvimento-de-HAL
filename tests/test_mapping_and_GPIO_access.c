#include "../ext/Unity/unity.h"
#include "HAL_mock.h"

void setUp(void) {  
  PINB_Mock = 0;
  PORTB_Mock = 0;
};

void tearDown(void) {};

void test_1_pin_conversion_and_assignment(void) {  
  MAP_IO(out_mp_test, LED_XA, &PORTB_Mock, PINS{PB0});
  TEST_ASSERT_EQUAL(0b00000001, out_mp_test[LED_XA].pins);
}

void test_multi_pin_conversion_and_assignment(void) {    
  MAP_IO(out_mp_test, DISPLAY_SEVEN, &PORTB_Mock, (PINS{PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7}));
  TEST_ASSERT_EQUAL(0b11111111, out_mp_test[DISPLAY_SEVEN].pins);
}

void test_set_bits(void) {
  MAP_IO(out_mp_test, FOUR_BAR_LED, &PORTB_Mock, (PINS{PB0, PB2, PB4, PB6}));
  set_output_Service(FOUR_BAR_LED);
  TEST_ASSERT_EQUAL(0b01010101, PORTB_Mock);
}

void test_clear_bits_does_not_corrupt_port_value(void) {
  MAP_IO(out_mp_test, FOUR_BAR_LED, &PORTB_Mock, (PINS{PB0, PB2, PB4, PB6}));  
  PORTB_Mock |= 0b11111111; //init port  
  clear_outputs_Service(FOUR_BAR_LED);
  TEST_ASSERT_EQUAL(0b10101010, PORTB_Mock);
}

void test_flip_bits(void) {
  MAP_IO(out_mp_test, FOUR_BAR_LED, &PORTB_Mock, (PINS{PB0, PB2, PB4, PB6}));  
  PORTB_Mock |= 0b11111111; //init port  
  flip_outputs_Service(FOUR_BAR_LED);
  TEST_ASSERT_EQUAL(0b10101010, PORTB_Mock);
  
  flip_outputs_Service(FOUR_BAR_LED);
  TEST_ASSERT_EQUAL(0b11111111, PORTB_Mock);
}

void test_bit_reading_passes(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTB_Mock, (PINS{PB3, PB4}));  
  PORTB_Mock = 0b00010000;
  unsigned int read = read_inputs_Service(SIDE_SENSORS);
  TEST_ASSERT_EQUAL(0b00010000, read);
  
  PORTB_Mock = 0b00011000;
  read = read_inputs_Service(SIDE_SENSORS);
  TEST_ASSERT_EQUAL(0b00011000, read);
  
  PORTB_Mock = 0b00001000;
  read = read_inputs_Service(SIDE_SENSORS);
  TEST_ASSERT_EQUAL(0b00001000, read);
}

void test_bit_reading_fails(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTB_Mock, (PINS{PB3, PB4}));  
  PORTB_Mock = 0b01000000;
  unsigned int read = read_inputs_Service(SIDE_SENSORS);
  TEST_ASSERT_NOT_EQUAL(0b00011000, read);
  TEST_ASSERT_NOT_EQUAL(0b00001000, read);
  TEST_ASSERT_NOT_EQUAL(0b00010000, read);
}

void test_get_single_input_device_pin(void) {
  MAP_IO(in_mp_test, RIGHT_SNSR, &PINB_Mock, (PINS{PB0}));
  MAP_IO(in_mp_test, LEFT_SNSR, &PINB_Mock, (PINS{PB1}));
  char pins = get_input_pins_Service(RIGHT_SNSR);
  TEST_ASSERT_EQUAL(0b00000001, pins);
  
  pins = get_input_pins_Service(LEFT_SNSR);
  TEST_ASSERT_EQUAL(0b00000010, pins);
}

void test_composite_device_pins_are_the_same_as_single_input_device_pins(void) {
  MAP_IO(in_mp_test, RIGHT_SNSR, &PINB_Mock, (PINS{PB0}));
  MAP_IO(in_mp_test, LEFT_SNSR, &PINB_Mock, (PINS{PB1}));
  MAP_IO(in_mp_test, SIDE_SENSORS, &PINB_Mock, (PINS{PB0, PB1}));
  char right_snsr_pin = get_input_pins_Service(RIGHT_SNSR);
  char left_snsr_pin = get_input_pins_Service(LEFT_SNSR);
  char lateral_snsr_pins = get_input_pins_Service(SIDE_SENSORS);
  char composite_side_sensor_pins = (right_snsr_pin | left_snsr_pin);
  TEST_ASSERT_EQUAL(lateral_snsr_pins, composite_side_sensor_pins);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_1_pin_conversion_and_assignment);
  RUN_TEST(test_multi_pin_conversion_and_assignment);
  RUN_TEST(test_set_bits);
  RUN_TEST(test_clear_bits_does_not_corrupt_port_value);
  RUN_TEST(test_flip_bits);
  RUN_TEST(test_bit_reading_passes);
  RUN_TEST(test_bit_reading_fails);
  RUN_TEST(test_get_single_input_device_pin);
  RUN_TEST(test_composite_device_pins_are_the_same_as_single_input_device_pins);
  return UNITY_END();
}
