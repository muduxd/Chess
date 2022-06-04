CC = g++
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lsdl2_image -lsdl2_mixer 


INCLUDE = -Iinclude 
LIB = -Llib
CLASSES = -Isrc/classes/square -Isrc/classes/text
UTILS = -Isrc/utilities


TARGET = bin/main.exe
ENTRY = main.cpp
AUXILIARY = src/classes/square/Square.cpp src/classes/text/Text.cpp src/utilities/auxiliary.cpp src/utilities/colors.cpp


all:
	$(CC) $(INCLUDE) $(LIB) $(CLASSES) $(UTILS) -o $(TARGET) $(ENTRY) $(AUXILIARY) $(LINKER_FLAGS)
	./$(TARGET)