#pragma once
#include <Square.h>
#include <SDL2/SDL.h>
#include <colors.h>
#include <iostream>
#include <map>


extern std::map<char, std::string> piecesImages;

void createCopy(int x, int y, int a, int b, char boardState[8][8], char boardCopy[8][8]);
bool kingcheck(int gameState, char boardCopy[8][8]);
bool legal(int firstRow, int firstCol, int secondRow, int secondCol, char boardState[8][8], int gameState);
void RenderState(int gameState, SDL_Renderer *renderer);
void RenderBoard(char boardState[8][8], SDL_Window *window, SDL_Renderer *renderer);