#include <Board.h>


Board::Board(SDL_Window *window, SDL_Renderer *renderer) {
    Render(window, renderer);
}


void Board::Render(SDL_Window *window, SDL_Renderer *renderer) {
    restartButton = Text("Restart", black, yellow, 820, 350, 160, 50, renderer);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            SDL_Color color;

            if ((i + j)  % 2 == 0) 
                color = white;
            else
                color = green;
            

            if (boardState[i][j] == '0') Square(100, color, 100 * i, 100 * j, window, renderer);
            else Square(boardState[i][j], 100, color, 100 * i, 100 * j, window, renderer);
        }
    }
}


void Board::Restart(SDL_Window *window, SDL_Renderer *renderer) {
    gameState = WHITE_MOVES;
    isPieceSelected = false;
    fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    boardState[0][0] = 'r';
    boardState[0][1] = 'n';
    boardState[0][2] = 'b';
    boardState[0][3] = 'q';
    boardState[0][4] = 'k';
    boardState[0][5] = 'b';
    boardState[0][6] = 'n';
    boardState[0][7] = 'r';

    boardState[1][0] = 'p';
    boardState[1][1] = 'p';
    boardState[1][2] = 'p';
    boardState[1][3] = 'p';
    boardState[1][4] = 'p';
    boardState[1][5] = 'p';
    boardState[1][6] = 'p';
    boardState[1][7] = 'p';

    boardState[2][0] = '0';
    boardState[2][1] = '0';
    boardState[2][2] = '0';
    boardState[2][3] = '0';
    boardState[2][4] = '0';
    boardState[2][5] = '0';
    boardState[2][6] = '0';
    boardState[2][7] = '0';

    boardState[3][0] = '0';
    boardState[3][1] = '0';
    boardState[3][2] = '0';
    boardState[3][3] = '0';
    boardState[3][4] = '0';
    boardState[3][5] = '0';
    boardState[3][6] = '0';
    boardState[3][7] = '0';

    boardState[4][0] = '0';
    boardState[4][1] = '0';
    boardState[4][2] = '0';
    boardState[4][3] = '0';
    boardState[4][4] = '0';
    boardState[4][5] = '0';
    boardState[4][6] = '0';
    boardState[4][7] = '0';

    boardState[5][0] = '0';
    boardState[5][1] = '0';
    boardState[5][2] = '0';
    boardState[5][3] = '0';
    boardState[5][4] = '0';
    boardState[5][5] = '0';
    boardState[5][6] = '0';
    boardState[5][7] = '0';

    boardState[6][0] = 'P';
    boardState[6][1] = 'P';
    boardState[6][2] = 'P';
    boardState[6][3] = 'P';
    boardState[6][4] = 'P';
    boardState[6][5] = 'P';
    boardState[6][6] = 'P';
    boardState[6][7] = 'P';

    boardState[7][0] = 'R';
    boardState[7][1] = 'N';
    boardState[7][2] = 'B';
    boardState[7][3] = 'Q';
    boardState[7][4] = 'K';
    boardState[7][5] = 'B';
    boardState[7][6] = 'N';
    boardState[7][7] = 'R';

    Render(window, renderer);
}




void Board::handleLeftClick(SDL_Window *window, SDL_Renderer *renderer) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    

    if (gameState == WHITE_WIN || gameState == BLACK_WIN || gameState == DRAW) {
        return;
    }


    if (restartButton.isClicked(mouseX, mouseY)) {
        Restart(window, renderer);
        return;
    }
    

    int row = mouseY / 100;
    int collumn = mouseX / 100;


    if (isPieceSelected) {
        isPieceSelected = false;


        if (true) {
            if (boardState[row][collumn] == '0') 
                playSound(MOVE);
            else 
                playSound(CAPTURE);
            

            boardState[row][collumn] = before.piece;
            boardState[before.row][before.collumn] = '0';

            gameState = gameState == WHITE_MOVES ? BLACK_MOVES : WHITE_MOVES;
        }
        else {
            boardState[before.row][before.collumn] = before.piece;
        }

    }
    else if (boardState[row][collumn] != '0' && !isPieceSelected) {
        isPieceSelected = true;

        before.row = row;
        before.collumn = collumn;
        before.piece = boardState[row][collumn];

        selectedPiece = boardState[row][collumn];
    }

    Render(window, renderer);
}


void Board::handleRightClick(SDL_Window *window, SDL_Renderer *renderer) {

}


bool Board::isSelected() {
    return isPieceSelected;
}


char Board::getPosition(int row, int collumn) {
    return boardState[row][collumn];
}

char Board::getSelectedPiece() {
    return selectedPiece;
}


void Board::playSound(Sound type) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    switch (type) {
        case CAPTURE: {
            Mix_Chunk *captureEffect = Mix_LoadWAV("src/audio/capture.mp3");
            Mix_PlayChannel(1, captureEffect, 0);
            break;
        }

        
        case MOVE: {
            Mix_Chunk *moveEffect = Mix_LoadWAV("src/audio/move.mp3");
            Mix_PlayChannel(1, moveEffect, 0);
            break;
        }


        case END_GAME: {
            Mix_Chunk *endGameEffect = Mix_LoadWAV("src/audio/end_game.mp3");
            Mix_PlayChannel(1, endGameEffect, 0);
            break;
        }

        default:
            break;
    }
}