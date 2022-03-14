# Makefile: compilação dos testes
CC = gcc
SRC1 = ../src/convert_pins_to_bits.c test_convert_pins_to_bits.c
SRC2 = test_mapping_and_GPIO_access.c ../src/convert_pins_to_bits.c HAL_mock.h ../include/GPIO_register_pins_model.h samples.h  
UNITY = ../ext/Unity/unity.c
TARGET = tests.x

tests.x:	$(SRC1) $(SRC2)
		$(CC) $(SRC1) $(UNITY) -o $(TARGET)
		./$(TARGET)
		$(CC) $(SRC2) $(UNITY) -o $(TARGET)
		./$(TARGET)		
		rm $(TARGET)

clean:	
		rm $(TARGET)