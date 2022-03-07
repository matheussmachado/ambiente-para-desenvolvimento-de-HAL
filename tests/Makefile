# Makefile: compilação dos testes

all:	test_convert_pins_to_bits.x

test_convert_pins_to_bits.x:	test_convert_pins_to_bits.c
		gcc test_convert_pins_to_bits.c ../src/convert_pins_to_bits.c ../ext/Unity/unity.c -o test_convert_pins_to_bits.x -lm
		./test_convert_pins_to_bits.x
		rm test_convert_pins_to_bits.x

clean:	
		rm test_convert_pins_to_bits.x