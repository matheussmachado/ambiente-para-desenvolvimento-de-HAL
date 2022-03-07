int convert_pins_to_bits(int num_pins, int pins[]) {  
  int byte_val = 0b00000000;
  for (int i = 0; i < num_pins; i++) {
    byte_val |= (1 << pins[i]);
  }
  return byte_val;
}