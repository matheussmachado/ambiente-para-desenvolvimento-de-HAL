# Makefile: compilação dos testes
CC = gcc
SRC1 = ../src/convert_pins_to_bits.c test_convert_pins_to_bits.c
SRC2 = ../src/convert_pins_to_bits.c ../include/GPIO_Register_Pins_Model.h test_mapping_and_GPIO_access.c 
UNITY = ../ext/Unity/unity.c
TARGET = tests.x

tests.x:	$(SRC1) $(SRC2)
		$(CC) $(SRC1) $(UNITY) -o $(TARGET) -lm
		./$(TARGET)
		$(CC) $(SRC2) $(UNITY) -o $(TARGET) -lm
		./$(TARGET)
		rm $(TARGET)

clean:	
		rm $(TARGET)