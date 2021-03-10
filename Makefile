CC = g++
OUT_DIR = build
CFLAGS = -c -Wall -Werror -Wpedantic -Wunreachable-code -Wextra -g
TFLAGS = -D TEST
INC = -I includes
all : algo

algo : main.o lib.o Rectangle.o  # Add other .o files here
		$(CC) main.o Rectangle.o lib.o -o algo
		@mkdir -p $(OUT_DIR)
		@mv *.o $(OUT_DIR)
		@mv algo $(OUT_DIR)

test:   main_test.o
			$(CC) main.o -o alco
		    @mkdir -p $(OUT_DIR)
		    @mv *.o $(OUT_DIR)
		    @mv algo $(OUT_DIR)

main.o : main.cpp
			$(CC) $(CFLAGS) main.cpp $(OUTPUT) $(INC)

lib.o : lib.cpp
			$(CC) $(CFLAGS) lib.cpp $(OUTPUT) $(INC)
			
Rectangle.cpp : Rectangle.cpp
			$(CC) $(CFLAGS) Rectangle.cpp $(OUTPUT) $(INC)

main_test.o : main.cpp
			$(CC) $(CFLAGS) $(TFLAGS) main.cpp $(OUTPUT) $(INC)

clean : 
			rm -rf $(OUT_DIR) compiler
			