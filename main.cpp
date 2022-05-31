#include <SDL2/SDL.h>
#include <iostream>
#include <colors.h>
#include <Square.h>
#include <map>


#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800


void RenderBoard(std::string str, std::map<char, std::string> &piecesImages) {
    // Square *board[8][8];

    // int i=0;
    // int j = 0;

    //     for (int k=0; k<strlen(str); k++)
    //     {
    //         if(str[k]>47 && str[k]<58)
    //         {

    //             for(int c=i;c<atoi((str[k]));c++)
    //                 board[c][j] = new Square( 100, color, 100 * i, 100 * j, window, renderer);
    //                 i=c;
    //         }
    //         else 
    //             switch (str[k])
    //             {
    //             case '/':
    //                 board[i][j] = new Square( 100, color, 100 * i, 100 * j, window, renderer, piecesImages);
    //                 j++;
    //                 break;
    //             default:
    //             int c=atoi(str[k]);
    //             i++;

    //             }
    //             k++;
    //     }
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


    SDL_Surface* icon = SDL_LoadBMP("src/images/icon.bmp");
    SDL_SetWindowIcon(window, icon);


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cout << "Error: Failed to create renderer\nSDL Error: '%s'\n" << SDL_GetError() << std::endl;
        return 1;
    }


    std::string board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    std::map<char, std::string> piecesImages {
        {'p', ""},
        {'r', ""},
        {'n', ""},
        {'b', ""},
        {'k', ""},
        {'q', ""},
        {'P', ""},
        {'R', ""},
        {'N', ""},
        {'B', ""},
        {'K', ""},
        {'Q', ""}
    };

    


    bool running = true;
    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.g, black.a);
        SDL_RenderClear(renderer);

        RenderBoard(board, piecesImages);

        SDL_RenderPresent(renderer);
    }

    return 0;
}