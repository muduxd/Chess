#include <Text.h>


Text::Text(){}

Text::Text(std::string text, SDL_Color textColor, SDL_Color backgroundColor, int x, int y, int width, int height, SDL_Renderer *renderer) :
    text(text), textColor(textColor), backgroundColor(backgroundColor), x(x), y(y), width(width), height(height) {

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);


    SDL_Rect rectangle { x, y, width, height };
    TTF_Font *font = TTF_OpenFont("src/fonts/Roboto-Medium.ttf", 32);

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, textColor.g, textColor.b, textColor.a);


    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);




    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderCopy(renderer, textureText, NULL, &rectangle);
}



bool Text::isClicked(int mouseX, int mouseY) {
    if (mouseX >= x && mouseX <= (x + width) && mouseY >=y && mouseY <= (y + height))
        return true;
    return false;
}