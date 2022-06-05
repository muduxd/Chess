#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>


class Text {
    private:
        int x, y, width, height;
        SDL_Color textColor, backgroundColor;
        std::string text;

    public: 
        Text();
        Text(std::string text, SDL_Color textColor, SDL_Color backgroundColor, int x, int y, int width, int height, SDL_Renderer *renderer);
        bool isClicked(int mouseX, int mouseY);
};