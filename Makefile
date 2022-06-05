CC = g++
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lsdl2_image -lsdl2_mixer -lsdl2_ttf


INCLUDE = -Iinclude 
LIB = -Llib
CLASSES = -Isrc/classes/board -Isrc/classes/square -Isrc/classes/text 
UTILS = -Isrc/utilities/colors


TARGET = bin/main.exe
ENTRY = main.cpp
AUXILIARY = src/classes/board/Board.cpp src/classes/square/Square.cpp src/classes/text/Text.cpp src/utilities/colors/Colors.cpp


all:
	$(CC) $(INCLUDE) $(LIB) $(CLASSES) $(UTILS) -o $(TARGET) $(ENTRY) $(AUXILIARY) $(LINKER_FLAGS)
	./$(TARGET)