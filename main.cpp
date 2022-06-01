#include <SDL2/SDL.h>
#include <iostream>
#include <Square.h>
#include <auxiliary.h>


#define SCREEN_WIDTH 1000 
#define SCREEN_HEIGHT 800




int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);


    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    SDL_Surface* icon = IMG_Load("src/images/icon.png");
    SDL_SetWindowIcon(window, icon);



    struct Point {
        int row, col;
        char piece;
    } first;


    char boardState[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    };


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    RenderBoard(boardState, window, renderer);
    

    bool running = true;
    bool selected = false;
    char selectedPiece;


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


                        if (selected == true) {
                            selected = false;

                            if (legal(first.row, first.col, row, collumn, boardState)) 
                                boardState[row][collumn] = first.piece;
                            else 
                                boardState[first.row][first.col] = first.piece;
                            
                            
                            RenderBoard(boardState, window, renderer);

                        }
                        else if (boardState[row][collumn] != '0' && selected == false) {
                            selected = true;

                            first.row = row;
                            first.col = collumn;
                            first.piece = boardState[row][collumn];


                            selectedPiece = boardState[row][collumn];
                            boardState[row][collumn] = '0';
                        }

                    }

                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        std::cout << "Right click" << std::endl;
                    }

                    break;

                default:
                    break;
            }


            if (selected) {
                int mouseX, mouseY;

                SDL_GetMouseState(&mouseX, &mouseY);
                char* imageURL = strcpy(new char[piecesImages[selectedPiece].length() + 1], piecesImages[selectedPiece].c_str());

                SDL_Rect rectangle { mouseX - 50, mouseY - 50, 100, 100 };
                SDL_Texture* image = IMG_LoadTexture(renderer, imageURL);

                RenderBoard(boardState, window, renderer);
                SDL_RenderCopy(renderer, image, NULL, &rectangle);
            }


        }



        SDL_RenderPresent(renderer);
    }


    return 0;
}