#include <auxiliary.h>
#include <colors.h>

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



bool legal(int firstRow, int firstCol, int secondRow, int secondCol, char boardState[8][8]) {
    if (firstRow == secondRow && firstCol == secondCol) return false;

    return true;
}


void RenderBoard(char boardState[8][8], SDL_Window *window, SDL_Renderer *renderer) {
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