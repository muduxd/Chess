#include <Text.h>


Text::Text(std::string text, SDL_Color textColor, SDL_Color backgroundColor, int x, int y, int width, int height, SDL_Renderer *renderer) :
    text(text), textColor(textColor), backgroundColor(backgroundColor), x(x), y(y), width(width), height(height) {

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_Rect rectangle { x, y, width, height };
    SDL_RenderFillRect(renderer, &rectangle);
}

bool Text::isClicked(int mouseX, int mouseY) {
    if (mouseX >= x && mouseX <= (x + width) && mouseY >=y && mouseY <= (y + height))
        return true;
    return false;
}