all:
	g++ -Isrc/Include -Lsrc/lib -Isrc/utilities -Isrc/classes/square -o main main.cpp src/classes/square/square.cpp -lmingw32 -lSDL2main -lSDL2 -lsdl2_image