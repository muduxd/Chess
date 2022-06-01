#include <SDL2/SDL.h>
#include <iostream>
#include <colors.h>
#include <Square.h>
#include <map>


#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800


void RenderBoard(char boardState[8][8], SDL_Window *window, SDL_Renderer *renderer, std::map<char, std::string> &piecesImages) {
    Square* board[8][8];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            SDL_Color color;

            if ((i + j)  % 2 == 0) 
                color = white;
            else
                color = black;
            

            if (boardState[i][j] == '0') board[i][j] = new Square(100, color, 100 * i, 100 * j, window, renderer);
            else board[i][j] = new Square(boardState[i][j], 100, color, 100 * i, 100 * j, window, renderer, piecesImages);
        }
    }
}



int main(int argc, char** argv) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error: SDL failed to initialize\nSDL Error: '%s'\n" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window) {
        std::cout << "Error: Failed to open window\nSDL Error: '%s'\n" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cout << "Error: Failed to create renderer\nSDL Error: '%s'\n" << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Surface* icon = IMG_Load("src/images/icon.png");
    SDL_SetWindowIcon(window, icon);


    char boardState[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'P', 'P', 'B', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };

    std::map<char, std::string> piecesImages {
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

    RenderBoard(boardState, window, renderer, piecesImages);
    


    bool running = true;
    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;


                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX, mouseY;

                        SDL_GetMouseState(&mouseX, &mouseY);
                        int row = mouseY / 100;
                        int collumn = mouseX / 100;

                        if (boardState[row][collumn] != '0') {
                            std::cout << boardState[row][collumn] << std::endl;
                        }
                    }

                    else if (event.button.button == SDL_BUTTON_RIGHT)
                        RenderBoard(boardState, window, renderer, piecesImages);

                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.g, black.a);


        SDL_RenderPresent(renderer);
    }

    return 0;
}