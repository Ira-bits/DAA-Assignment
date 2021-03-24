CC = g++
OUT_DIR = build
CFLAGS = -c -Wall -Werror -Wpedantic -Wunreachable-code -Wextra -g -std=c++17 -O2
TFLAGS = -D TEST
INC = -I includes
.PHONY: test clean
all : algo

algo : main.o Rectangle.o lib.o RectangleSet.o stripes.o # Add other .o files here
		$(CC) main.o Rectangle.o lib.o RectangleSet.o stripes.o -o algo
		@mkdir -p $(OUT_DIR)
		@mv *.o $(OUT_DIR)
		@mv algo $(OUT_DIR)

main.o : src/main.cpp
			$(CC) $(CFLAGS) src/main.cpp $(OUTPUT) $(INC)

Rectangle.o : src/Rectangle.cpp
			$(CC) $(CFLAGS) src/Rectangle.cpp $(OUTPUT) $(INC)

RectangleSet.o : src/RectangleSet.cpp
			$(CC) $(CFLAGS) src/RectangleSet.cpp $(OUTPUT) $(INC)
		
stripes.o : src/stripes.cpp
			$(CC) $(CFLAGS) src/stripes.cpp $(OUTPUT) $(INC)

lib.o : src/lib.cpp
			$(CC) $(CFLAGS) src/lib.cpp $(OUTPUT) $(INC)

test:
			./scripts/test

clean : 
			rm -rf $(OUT_DIR)
			
