unsigned int convert_pins_to_bits(unsigned int num_pins, unsigned int pins[]) {  
  int byte_val = 0b00000000;
  for (unsigned int i = 0; i < num_pins; i++) {
    byte_val |= (1 << pins[i]);
  }
  return byte_val;
}