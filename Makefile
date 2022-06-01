CC = g++

BIN = bin
INCLUDE = include 
LIB = lib
SOURCE = src/classes/square
UTILS = src/utilities

TARGET = bin/main.exe
ENTRY = main.cpp


all:
	$(CC) -I$(INCLUDE) -L$(LIB) -I$(SOURCE) -I$(UTILS) -o $(TARGET) $(ENTRY) src/classes/square/Square.cpp -lmingw32 -lSDL2main -lSDL2 -lsdl2_image
	./$(TARGET)