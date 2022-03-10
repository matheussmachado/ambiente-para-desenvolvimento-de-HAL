#include "../ext/Unity/unity.h"
#include "../include/GPIO_Register_Pins_Model.h"
#include <stdio.h>

// CRIAÇÃO DE AMBIENTE PARA TESTES
//==============================================================================
#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7

typedef enum output_devices_ids {
  LED_XA, LED_XB, DISPLAY_SEVEN, FOUR_BAR_LED, END_OUTPUT_DEV_TEST
} out_dev_id;

typedef enum input_devices_ids {
  SIDE_SENSORS, END_INPUT_DEV_TEST
} oin_dev_id;

typedef GPIO_Register_Pins output_devices_pins_mapper_test[END_OUTPUT_DEV_TEST];
output_devices_pins_mapper_test out_mp_test;
typedef GPIO_Register_Pins input_devices_pins_mapper_test[END_INPUT_DEV_TEST];
output_devices_pins_mapper_test in_mp_test;
int PORTx_Mock;
//==============================================================================

void setUp(void) {
  output_devices_pins_mapper_test out_mp_test;
  int PORTx_Mock = 0;
};

void tearDown(void) {};

void test_1_pin_conversion_and_assignment(void) {  
  MAP_IO(out_mp_test, LED_XA, &PORTx_Mock, PINS{PB0});
  TEST_ASSERT_EQUAL(0b00000001, out_mp_test[LED_XA].pins);
}

void test_multi_pin_conversion_and_assignment(void) {    
  MAP_IO(out_mp_test, DISPLAY_SEVEN, &PORTx_Mock, (PINS{PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7}));
  TEST_ASSERT_EQUAL(0b11111111, out_mp_test[DISPLAY_SEVEN].pins);
}

void test_set_bits(void) {
  MAP_IO(out_mp_test, FOUR_BAR_LED, &PORTx_Mock, (PINS{PB0, PB2, PB4, PB6}));
  *(int*)(out_mp_test[FOUR_BAR_LED].register_pointer) |= out_mp_test[FOUR_BAR_LED].pins; //set bits
  TEST_ASSERT_EQUAL(0b01010101, PORTx_Mock);
}

void test_clear_bits_does_not_corrupt_port_value(void) {
  MAP_IO(out_mp_test, FOUR_BAR_LED, &PORTx_Mock, (PINS{PB0, PB2, PB4, PB6}));  
  PORTx_Mock |= 0b11111111; //init port  
  *(int*)(out_mp_test[FOUR_BAR_LED].register_pointer) &= ~(out_mp_test[FOUR_BAR_LED].pins); //clear bits
  TEST_ASSERT_EQUAL(0b10101010, PORTx_Mock);
}

void test_flip_bits(void) {
  MAP_IO(out_mp_test, FOUR_BAR_LED, &PORTx_Mock, (PINS{PB0, PB2, PB4, PB6}));  
  PORTx_Mock |= 0b11111111; //init port  
  *(int*)(out_mp_test[FOUR_BAR_LED].register_pointer) ^= out_mp_test[FOUR_BAR_LED].pins; //flip bits
  TEST_ASSERT_EQUAL(0b10101010, PORTx_Mock);
  *(int*)(out_mp_test[FOUR_BAR_LED].register_pointer) ^= out_mp_test[FOUR_BAR_LED].pins; //flip bits
  TEST_ASSERT_EQUAL(0b11111111, PORTx_Mock);
}

void test_bits_test_is_true(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTx_Mock, (PINS{PB3, PB4}));
  *(int*)(out_mp_test[FOUR_BAR_LED].register_pointer) |= in_mp_test[SIDE_SENSORS].pins; //sensors setted
  TEST_ASSERT_TRUE(PORTx_Mock & in_mp_test[SIDE_SENSORS].pins);
}

void test_bits_test_is_false(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTx_Mock, (PINS{PB3, PB4}));  
  PORTx_Mock = 0; //sensors not setted
  TEST_ASSERT_FALSE(PORTx_Mock & in_mp_test[SIDE_SENSORS].pins);
}

void test_bits_test_with_different_port_and_mask_fail(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTx_Mock, (PINS{PB3, PB4}));  
  PORTx_Mock = 0b11000000; //no sensors were triggered
  // 0b11000000
  // 0b00011000 &
  // ------------
  // 0b00000000
  TEST_ASSERT_FALSE(PORTx_Mock & in_mp_test[SIDE_SENSORS].pins);
}

void test_bit_test_with_nearly_equal_port_and_mask_pass(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTx_Mock, (PINS{PB3, PB4}));  
  PORTx_Mock = 0b00010000; //only 1 sensor was triggered
  // PINx   ->   0b00010000
  // SENS   ->   0b00011000 &
  // -------------------------
  // RES    ->   0b00010000
  TEST_ASSERT_TRUE(PORTx_Mock & in_mp_test[SIDE_SENSORS].pins);
}

void test_bit_reading_passes(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTx_Mock, (PINS{PB3, PB4}));  
  PORTx_Mock = 0b00010000;
  unsigned int read = PORTx_Mock & in_mp_test[SIDE_SENSORS].pins;
  TEST_ASSERT_EQUAL(0b00010000, read);
  PORTx_Mock = 0b00011000;
  read = PORTx_Mock & in_mp_test[SIDE_SENSORS].pins;
  TEST_ASSERT_EQUAL(0b00011000, read);
  PORTx_Mock = 0b00001000;
  read = PORTx_Mock & in_mp_test[SIDE_SENSORS].pins;
  TEST_ASSERT_EQUAL(0b00001000, read);
}

void test_bit_reading_fails(void) {
  MAP_IO(in_mp_test, SIDE_SENSORS, &PORTx_Mock, (PINS{PB3, PB4}));  
  PORTx_Mock = 0b01000000;
  unsigned int read = PORTx_Mock & in_mp_test[SIDE_SENSORS].pins;
  TEST_ASSERT_NOT_EQUAL(0b00011000, read);
  TEST_ASSERT_NOT_EQUAL(0b00001000, read);
  TEST_ASSERT_NOT_EQUAL(0b00010000, read);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_1_pin_conversion_and_assignment);
  RUN_TEST(test_multi_pin_conversion_and_assignment);
  RUN_TEST(test_set_bits);
  RUN_TEST(test_clear_bits_does_not_corrupt_port_value);
  RUN_TEST(test_flip_bits);
  RUN_TEST(test_bits_test_is_true);
  RUN_TEST(test_bits_test_is_false);
  RUN_TEST(test_bits_test_with_different_port_and_mask_fail);
  RUN_TEST(test_bit_test_with_nearly_equal_port_and_mask_pass);
  RUN_TEST(test_bit_reading_passes);
  RUN_TEST(test_bit_reading_fails);
  return UNITY_END();
}
