#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <auxiliary.h>
#include <Text.h>


#define SCREEN_WIDTH 1000 
#define SCREEN_HEIGHT 800




int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);


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
    char boardCopy[8][8];


    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    RenderBoard(boardState, window, renderer);
    

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Mix_Chunk *captureEffect = Mix_LoadWAV("src/audio/capture.mp3");
    Mix_Chunk *moveEffect = Mix_LoadWAV("src/audio/move.mp3");
    

    bool running = true;
    bool selected = false;
    char selectedPiece;
    int gameState = 1;

    RenderState(gameState, renderer);
    Text restartButton = Text("Restart", black, yellow, 820, 350, 160, 50, renderer);

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

                        if (restartButton.isClicked(mouseX, mouseY)) {
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

                            gameState = 1;
                            selected = false;

                            RenderBoard(boardState, window, renderer);
                            RenderState(gameState, renderer);
                        }

                        int row = mouseY / 100;
                        int collumn = mouseX / 100;



                        if (selected == true) {
                            selected = false;


                            if (legal(first.row, first.col, row, collumn, boardState, gameState)) {
                                if (boardState[row][collumn] == '0')
                                    Mix_PlayChannel(1, moveEffect, 0);
                                else 
                                    Mix_PlayChannel(1, captureEffect, 0);


                                boardState[row][collumn] = first.piece;
                                boardState[first.row][first.col] = '0';

                                gameState = gameState == 1 ? 2 : 1;
                            }
                            else {
                                boardState[first.row][first.col] = first.piece;
                            }

                            RenderBoard(boardState, window, renderer);
                            RenderState(gameState, renderer);
                        }
                        else if (boardState[row][collumn] != '0' && selected == false) {
                            selected = true;

                            first.row = row;
                            first.col = collumn;
                            first.piece = boardState[row][collumn];


                            selectedPiece = boardState[row][collumn];
                        }
                    }

                    break;

                default:
                    break;
            }


            if (selected) {
                int mouseX, mouseY;

                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX < 770) {

                    char* imageURL = strcpy(new char[piecesImages[selectedPiece].length() + 1], piecesImages[selectedPiece].c_str());


                    SDL_Rect rectangle { mouseX - 50, mouseY - 50, 100, 100 };
                    SDL_Texture* image = IMG_LoadTexture(renderer, imageURL);

                    RenderBoard(boardState, window, renderer);
                    SDL_RenderCopy(renderer, image, NULL, &rectangle);
                }
            }


        }



        SDL_RenderPresent(renderer);
    }


    return 0;
}