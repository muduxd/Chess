#include <SDL2/SDL.h>
#include <Board.h>
#include <Square.h>


#define SCREEN_WIDTH 1200 
#define SCREEN_HEIGHT 800


int main (int argc, char *argv[]) {

    //INITIALIZE WINDOW

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    //SETTING APP ICON

    SDL_Surface *icon = IMG_Load("src/images/icon.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);


    //INITIALIZE BOARD

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    Board board(window, renderer);


    bool running = true;
    while (running) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        board.handleLeftClick(window, renderer);

                    else if (event.button.button == SDL_BUTTON_RIGHT)
                        board.handleRightClick(window, renderer);

                    break;

                default:
                    break;
            }


            if (board.isSelected()) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                

                if (mouseX < 770) {
                    char* imageURL = strcpy(new char[paths[board.getSelectedPiece()].length() + 1], paths[board.getSelectedPiece()].c_str());

                    SDL_Rect rectangle { mouseX - 50, mouseY - 50, 100, 100 };
                    SDL_Texture* image = IMG_LoadTexture(renderer, imageURL);

                    board.Render(window, renderer);
                    SDL_RenderCopy(renderer, image, NULL, &rectangle);
                    SDL_DestroyTexture(image);
                }
            }


        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}