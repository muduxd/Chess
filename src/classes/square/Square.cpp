#include <iostream>
#include <Square.h>


Square::Square(int width, SDL_Color color, int x, int y, SDL_Window *window, SDL_Renderer *renderer) : 
    piece('0'), width(width), color(color), x(x), y(y) {


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect rectangle { x, y, width, width };

    SDL_RenderFillRect(renderer, &rectangle);
}



Square::Square(char piece, int width, SDL_Color color, int x, int y, SDL_Window *window, SDL_Renderer *renderer, std::map<char, std::string> &piecesImages) : 
    piece(piece), width(width), color(color), x(x), y(y) {


    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Rect rectangle { x, y, width, width };
    SDL_Rect imageRect {y, x, width, width};


    char* imageURL = strcpy(new char[piecesImages[piece].length() + 1], piecesImages[piece].c_str());
    

    SDL_Texture* image = IMG_LoadTexture(renderer, imageURL);


    SDL_RenderCopy(renderer, image, NULL, &imageRect);
    SDL_RenderFillRect(renderer, &rectangle);
}


