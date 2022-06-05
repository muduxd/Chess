#include <Square.h>


std::map<char, std::string> paths {
    {'p', "src/images/black-pond.png"},
    {'r', "src/images/black-rook.png"},
    {'n', "src/images/black-knight.png"},
    {'b', "src/images/black-bishop.png"},
    {'k', "src/images/black-king.png"},
    {'q', "src/images/black-queen.png"},
    {'P', "src/images/white-pond.png"},
    {'R', "src/images/white-rook.png"},
    {'N', "src/images/white-knight.png"},
    {'B', "src/images/white-bishop.png"},
    {'K', "src/images/white-king.png"},
    {'Q', "src/images/white-queen.png"}
};


Square::Square(int width, SDL_Color color, int x, int y, SDL_Window *window, SDL_Renderer *renderer) : 
    piece('0'), width(width), color(color), x(x), y(y) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rectangle { y, x, width, width };
    SDL_RenderFillRect(renderer, &rectangle);
}



Square::Square(char piece, int width, SDL_Color color, int x, int y, SDL_Window *window, SDL_Renderer *renderer) : 
    piece(piece), width(width), color(color), x(x), y(y) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    char* imageURL = strcpy(new char[paths[piece].length() + 1], paths[piece].c_str());

    SDL_Rect rectangle { y, x, width, width };
    SDL_Texture *image = IMG_LoadTexture(renderer, imageURL);


    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderCopy(renderer, image, NULL, &rectangle);
    SDL_DestroyTexture(image);
}
