CC = g++
OUT_DIR = build
CFLAGS = -c -Wall -Werror -Wpedantic -Wunreachable-code -Wextra -g -std=c++17
TFLAGS = -D TEST
INC = -I includes
all : algo

algo : main.o Rectangle.o lib.o RectangleSet.o stripes.o # Add other .o files here
		$(CC) main.o Rectangle.o lib.o RectangleSet.o stripes.o -o algo
		@mkdir -p $(OUT_DIR)
		@mv *.o $(OUT_DIR)
		@mv algo $(OUT_DIR)

test:   main_test.o
			$(CC) main.o -o algo
		    @mkdir -p $(OUT_DIR)
		    @mv *.o $(OUT_DIR)
		    @mv algo $(OUT_DIR)

main.o : main.cpp
			$(CC) $(CFLAGS) main.cpp $(OUTPUT) $(INC)

Rectangle.o : Rectangle.cpp
			$(CC) $(CFLAGS) Rectangle.cpp $(OUTPUT) $(INC)

RectangleSet.o : RectangleSet.cpp
			$(CC) $(CFLAGS) RectangleSet.cpp $(OUTPUT) $(INC)
		
stripes.o : stripes.cpp
			$(CC) $(CFLAGS) stripes.cpp $(OUTPUT) $(INC)

lib.o : lib.cpp
			$(CC) $(CFLAGS) lib.cpp $(OUTPUT) $(INC)

main_test.o : main.cpp
			$(CC) $(CFLAGS) $(TFLAGS) main.cpp $(OUTPUT) $(INC)

test:
	./test

clean : 
			rm -rf $(OUT_DIR)
			