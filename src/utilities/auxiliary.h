#pragma once
#include <Square.h>
#include <SDL2/SDL.h>
#include <map>


extern std::map<char, std::string> piecesImages;

bool legal(int firstRow, int firstCol, int secondRow, int secondCol, char boardState[8][8]);
void RenderBoard(char boardState[8][8], SDL_Window *window, SDL_Renderer *renderer);