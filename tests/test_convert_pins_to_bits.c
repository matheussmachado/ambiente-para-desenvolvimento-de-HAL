#include "../ext/Unity/unity.h"
#include "../include/convert_pins_to_bits.h"

#define PB0     0
#define PB1     1
#define PB2     2
#define PB3     3
#define PB4     4
#define PB5     5
#define PB6     6
#define PB7     7
#define PINS (int[])

void setUp(void) {};
void tearDown(void) {};

void test_that_the_conversion_of_PB0_is_different_from_0(void) {
  TEST_ASSERT_NOT_EQUAL(0, convert_pins_to_bits(1, PINS{PB0}));
}

void test_one_pin_conversions(void) {
  TEST_ASSERT_EQUAL(0b00000001, convert_pins_to_bits(1, PINS{PB0}));
  TEST_ASSERT_EQUAL(0b00000010, convert_pins_to_bits(1, PINS{PB1}));
  TEST_ASSERT_EQUAL(0b00000100, convert_pins_to_bits(1, PINS{PB2}));
  TEST_ASSERT_EQUAL(0b00001000, convert_pins_to_bits(1, PINS{PB3}));
  TEST_ASSERT_EQUAL(0b00010000, convert_pins_to_bits(1, PINS{PB4}));
  TEST_ASSERT_EQUAL(0b00100000, convert_pins_to_bits(1, PINS{PB5}));
  TEST_ASSERT_EQUAL(0b01000000, convert_pins_to_bits(1, PINS{PB6}));
  TEST_ASSERT_EQUAL(0b10000000, convert_pins_to_bits(1, PINS{PB7}));
}

void test_two_pins_conversions(void) {
  TEST_ASSERT_EQUAL(0b00000011, convert_pins_to_bits(2, PINS{PB0, PB1}));
  TEST_ASSERT_EQUAL(0b00000101, convert_pins_to_bits(2, PINS{PB0, PB2}));
  TEST_ASSERT_EQUAL(0b10000001, convert_pins_to_bits(2, PINS{PB0, PB7}));
}

void test_three_pins_conversions(void) {
  TEST_ASSERT_EQUAL(0b00000111, convert_pins_to_bits(3, PINS{PB0, PB1, PB2}));
  TEST_ASSERT_EQUAL(0b00001110, convert_pins_to_bits(3, PINS{PB1, PB2, PB3}));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_that_the_conversion_of_PB0_is_different_from_0);
  RUN_TEST(test_one_pin_conversions);
  RUN_TEST(test_two_pins_conversions);
  RUN_TEST(test_three_pins_conversions);
  return UNITY_END();
}