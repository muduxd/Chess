#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Square.h>
#include <Text.h>
#include <Colors.h>


enum GameState {
    WHITE_MOVES,
    BLACK_MOVES,
    WHITE_WIN,
    BLACK_WIN,
    DRAW
};


enum Sound {
    MOVE,
    CAPTURE,
    END_GAME
};


struct MovesMade {
    int row, collumn;
    char piece;
};


class Board {
    private:
        Text restartButton;
        GameState gameState = WHITE_MOVES;
        MovesMade before;

        bool isPieceSelected = false;
        char selectedPiece = 'p';

        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
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
        
    public:
        Board(SDL_Window *window, SDL_Renderer *renderer);
        void Render(SDL_Window *window, SDL_Renderer *renderer);
        void Restart(SDL_Window *window, SDL_Renderer *renderer);
        void handleLeftClick(SDL_Window *window, SDL_Renderer *renderer);
        void handleRightClick(SDL_Window *window, SDL_Renderer *renderer);
        bool isSelected();
        char getPosition(int row, int collumn);
        char getSelectedPiece();
        void playSound(Sound type);
};