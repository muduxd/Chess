#include <Text.h>
#include <iostream>

Text::Text(){}

Text::Text(std::string text, SDL_Color textColor, SDL_Color backgroundColor, int x, int y, int width, int height, SDL_Renderer *renderer) :
    text(text), textColor(textColor), backgroundColor(backgroundColor), x(x), y(y), width(width), height(height) {

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect rectangle { x, y, width, height };
    SDL_RenderFillRect(renderer, &rectangle);

    
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("src/fonts/Grand9K.ttf", 60);
    SDL_Surface *surfaceText = TTF_RenderText_Blended(font, text.c_str(), textColor);
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);


    SDL_Rect textRec { x + 10, y + 10, width - 20, height - 20};
    SDL_SetRenderDrawColor(renderer, textColor.r, textColor.g, textColor.b, textColor.a);
    SDL_RenderCopy(renderer, textureText, NULL, &textRec);

    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textureText);
}



bool Text::isClicked(int mouseX, int mouseY) {
    if (mouseX >= x && mouseX <= (x + width) && mouseY >=y && mouseY <= (y + height))
        return true;
    return false;
}