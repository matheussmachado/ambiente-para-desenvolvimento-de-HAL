#include "../ext/Unity/unity.h"
#include "../include/convert_pins_to_bits.h"

void setUp(void) {};
void tearDown(void) {};

void test_that_the_conversion_of_0_is_different_from_0(void) {
  TEST_ASSERT_NOT_EQUAL(0, convert_pins_to_bits(1, (int[]){0}));
}

void test_one_pin_conversions(void) {
  TEST_ASSERT_EQUAL(0b00000001, convert_pins_to_bits(1, (int[]){0}));
  TEST_ASSERT_EQUAL(0b00000010, convert_pins_to_bits(1, (int[]){1}));
  TEST_ASSERT_EQUAL(0b00000100, convert_pins_to_bits(1, (int[]){2}));
  TEST_ASSERT_EQUAL(0b00001000, convert_pins_to_bits(1, (int[]){3}));
  TEST_ASSERT_EQUAL(0b00010000, convert_pins_to_bits(1, (int[]){4}));
  TEST_ASSERT_EQUAL(0b00100000, convert_pins_to_bits(1, (int[]){5}));
  TEST_ASSERT_EQUAL(0b01000000, convert_pins_to_bits(1, (int[]){6}));
  TEST_ASSERT_EQUAL(0b10000000, convert_pins_to_bits(1, (int[]){7}));
}

void test_two_pins_conversions(void) {
  TEST_ASSERT_EQUAL(0b00000011, convert_pins_to_bits(2, (int[]){0, 1}));
  TEST_ASSERT_EQUAL(0b00000101, convert_pins_to_bits(2, (int[]){0, 2}));
  TEST_ASSERT_EQUAL(0b10000001, convert_pins_to_bits(2, (int[]){0, 7}));
}

void test_three_pins_conversions(void) {
  TEST_ASSERT_EQUAL(0b00000111, convert_pins_to_bits(3, (int[]){0, 1, 2}));
  TEST_ASSERT_EQUAL(0b00001110, convert_pins_to_bits(3, (int[]){1, 2, 3}));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_that_the_conversion_of_0_is_different_from_0);
  RUN_TEST(test_one_pin_conversions);
  RUN_TEST(test_two_pins_conversions);
  RUN_TEST(test_three_pins_conversions);
  return UNITY_END();
}