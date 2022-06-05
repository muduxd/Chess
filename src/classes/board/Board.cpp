#include <Board.h>


Board::Board(SDL_Window *window, SDL_Renderer *renderer) {
    Render(window, renderer);
}


void Board::Render(SDL_Window *window, SDL_Renderer *renderer) {
    restartButton = Text("Restart", white, black, 920, 380, 160, 50, renderer);

    Text whitePlayer = Text("You", white, black, 900, 700, 100, 50, renderer);
    Text whiteTurn = Text("", white, gameState == WHITE_MOVES ? grey : black, 1050, 700, 100, 50, renderer);

    Text blackPlayer = Text(" AI ", white, black, 900, 50, 100, 50, renderer);
    Text blackTurn = Text("", white, gameState == BLACK_MOVES ? grey : black, 1050, 50, 100, 50, renderer);


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


        if (moveValid(before.row, before.collumn, row, collumn)) {
            if (boardState[row][collumn] == '0') 
                playSound(MOVE);
            else 
                playSound(CAPTURE);
            

            boardState[row][collumn] = before.piece;
            boardState[before.row][before.collumn] = '0';

            gameState = gameState == WHITE_MOVES ? BLACK_MOVES : WHITE_MOVES;
        }
        else 
            boardState[before.row][before.collumn] = before.piece;
        
        Render(window, renderer);

    }
    else if (boardState[row][collumn] != '0' && !isPieceSelected) {
        isPieceSelected = true;

        before.row = row;
        before.collumn = collumn;
        before.piece = boardState[row][collumn];

        selectedPiece = boardState[row][collumn];
    }

}


void Board::handleRightClick(SDL_Window *window, SDL_Renderer *renderer) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int row = mouseY / 100;
    int collumn = mouseX / 100;

    if (boardState[row][collumn] == '0') Square(100, blue, 100 * row, 100 * collumn, window, renderer);
    else Square(boardState[row][collumn], 100, blue, 100 * row, 100 * collumn, window, renderer);
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

bool Board::moveValid(int firstRow, int firstCol, int secondRow, int secondCol) {
    if (
        (boardState[firstRow][firstCol] == 'r' || boardState[firstRow][firstCol] == 'n' || 
        boardState[firstRow][firstCol] == 'b' || boardState[firstRow][firstCol] == 'q' ||
        boardState[firstRow][firstCol] == 'k' || boardState[firstRow][firstCol] == 'p') && (gameState == WHITE_MOVES)
    )   return false;

    if (
        (boardState[firstRow][firstCol] == 'R' || boardState[firstRow][firstCol] == 'N' || 
        boardState[firstRow][firstCol] == 'B' || boardState[firstRow][firstCol] == 'Q' ||
        boardState[firstRow][firstCol] == 'K' || boardState[firstRow][firstCol] == 'P') && (gameState == BLACK_MOVES)
    )   return false;

    if (firstRow == secondRow && firstCol == secondCol) 
        return false;

    // if (gameState==2 && (boardState[firstRow][firstCol]>64 && boardState[firstRow][firstCol]<97 
    //     || boardState[secondRow][secondCol]>97))
    //     return 0;
    // if (gameState==1 && (boardState[firstRow][firstCol]>97 || (boardState[secondRow][secondCol]<97 && boardState[secondRow][secondCol]>64)))
    //     return 0;

    //     if(boardState[firstRow][firstCol]=='0')
    //         return 0;
        
    //     if(boardState[firstRow][firstCol]=='R' && gameState==1 || boardState[firstRow][firstCol]=='r' && gameState==2)
    //     {
    //         if(firstRow==secondRow && firstCol<secondCol)
    //             for(int i=firstCol+1;i<secondCol;i++)
    //             if(boardState[firstRow][i]!='0')
    //                 return 0;
    //         if(firstRow==secondRow && firstCol>secondCol)
    //             for(int i=firstCol-1;i>secondCol;i--)
    //             if(boardState[firstRow][i]!='0')
    //                 return 0;
    //         if(firstCol==secondCol && firstRow<secondRow)
    //             for(int i=firstRow+1;i<secondRow;i++)
    //             if(boardState[i][firstCol]!='0')
    //                 return 0;
    //         if(firstCol==secondCol && firstRow>secondRow)
    //             for(int i=firstRow-1;i>secondRow;i--)
    //             if(boardState[i][firstCol]!='0')
    //                 return 0;
    //         return 1;
    //     }
    //     if(boardState[firstRow][firstCol]=='N' && gameState==1 || boardState[firstRow][firstCol]=='n' && gameState==2)
    //     {
    //         if(  (secondRow==firstRow+2 && secondCol==firstCol+1) ||(secondRow==firstRow+2 && secondCol==firstCol-1)
    //            ||(secondRow==firstRow-2 && secondCol==firstCol+1) ||(secondRow==firstRow-2 && secondCol==firstCol-1)
    //            ||(secondRow==firstRow+1 && secondCol==firstCol+2) ||(secondRow==firstRow+1 && secondCol==firstCol-2)
    //            ||(secondRow==firstRow-1 && secondCol==firstCol+2) ||(secondRow==firstRow-1 && secondCol==firstCol-2))
    //            return 1;
                    
    //         else return 0;
    //     }
    //     if(boardState[firstRow][firstCol]=='B' && gameState==1 || boardState[firstRow][firstCol]=='b' && gameState==2)
    //     {
    //         int i=1;
    //         if(firstRow<secondRow && firstCol<secondCol)
    //             for(;i<secondRow-firstRow;i++)
    //                     if(boardState[firstRow+i][firstCol+i]!='0')
    //                         return 0;
    //         if(firstRow>secondRow && firstCol>secondCol)
    //             for(;i<firstRow-secondRow;i++)
    //                     if(boardState[firstRow-i][firstCol-i]!='0')
    //                         return 0;
    //         if(firstRow<secondRow && firstCol>secondCol)
    //             for(;i<secondRow-firstRow;i++)
    //                     if(boardState[firstRow+i][firstCol-i]!='0')
    //                         return 0;
    //         if(firstRow>secondRow && firstCol<secondCol)
    //             for(;i<firstRow-secondRow;i++)
    //                     if(boardState[firstRow-i][firstCol+i]!='0')
    //                         return 0;
    //         if(abs(secondRow-firstRow)==i && abs(secondCol-firstCol)==i)
    //             return 1;
    //         return 0;
    //     }
    //     if(boardState[firstRow][firstCol]=='Q' && gameState==1 || boardState[firstRow][firstCol]=='q' && gameState==2)
    //     {
    //         if(firstRow==secondRow && firstCol<secondCol)
    //             for(int i=firstCol+1;i<secondCol;i++)
    //             if(boardState[firstRow][i]!='0')
    //                 return 0;
    //         if(firstRow==secondRow && firstCol>secondCol)
    //             for(int i=firstCol-1;i>secondCol;i--)
    //             if(boardState[firstRow][i]!='0')
    //                 return 0;
    //         if(firstCol==secondCol && firstRow<secondRow)
    //             for(int i=firstRow+1;i<secondRow;i++)
    //             if(boardState[i][firstCol]!='0')
    //                 return 0;
    //         if(firstCol==secondCol && firstRow>secondRow)
    //             for(int i=firstRow-1;i>secondRow;i--)
    //             if(boardState[i][firstCol]!='0')
    //                 return 0;
    //                 int i=1,ok=0;
    //         if(firstRow<secondRow && firstCol<secondCol)
    //             for(ok=1;i<secondRow-firstRow;i++)
    //                     if(boardState[firstRow+i][firstCol+i]!='0')
    //                         return 0;
    //         if(firstRow>secondRow && firstCol>secondCol)
    //             for(ok=1;i<firstRow-secondRow;i++)
    //                     if(boardState[firstRow-i][firstCol-i]!='0')
    //                         return 0;
    //         if(firstRow<secondRow && firstCol>secondCol)
    //             for(ok=1;i<secondRow-firstRow;i++)
    //                     if(boardState[firstRow+i][firstCol-i]!='0')
    //                         return 0;
    //         if(firstRow>secondRow && firstCol<secondCol)
    //             for(ok=1;i<firstRow-secondRow;i++)
    //                     if(boardState[firstRow-i][firstCol+i]!='0')
    //                         return 0;
    //         if(ok)
    //         if(abs(secondRow-firstRow)==i && abs(secondCol-firstCol)==i)
    //             return 1;
    //         else return 0;
    //         return 1;

    //     }
        
    //     if(boardState[firstRow][firstCol]=='P' && gameState==1)
    //     {
            
    //         if(secondCol==firstCol)
    //         if(boardState[secondRow][secondCol]!='0')
    //         return 0;
    //         if(secondCol==firstCol)
    //             if(secondRow!=firstRow-1 && (firstRow!=6 && secondRow==firstRow-2))
    //                 return 0;

    //         if((secondCol!=firstCol+1 || secondCol!=firstCol-1) && secondRow!=firstRow-1)
    //         if(boardState[secondRow][secondCol]!='0')
    //             return 0;
               
    //         return 1;
    //     }
    //     if(boardState[firstRow][firstCol]=='p' && gameState==2)
    //     {
    //         if(secondCol==firstCol)
    //         if(boardState[secondRow][secondCol]!='0')
    //         return 0;
    //         if(secondCol==firstCol)
    //             if(secondRow!=firstRow+1 && (firstRow!=1 && secondRow==firstRow+2))
    //                 return 0;

    //         if((secondCol!=firstCol+1 || secondCol!=firstCol-1) && secondRow!=firstRow+1)
    //         if(boardState[secondRow][secondCol]!='0')
    //             return 0;
               
    //         return 1;
    //     }

    //     if(boardState[firstRow][firstCol]=='K' && gameState==1 || boardState[firstRow][firstCol]=='k' && gameState==2)
    //         if(abs(secondRow-firstRow)>1 || abs(secondCol-firstCol)>1)
    //             return 0;
    //         else return 1;


    return true;
}



bool Board::kingcheck() {

    char king = gameState == WHITE_MOVES ? 'K' : 'k';


    for (int i=0;i<8;i++)
        for (int j=0;j<8;j++)
        {
            if(boardCopy[i][j]=='0' || boardCopy[i][j]==king)
                continue;

            if(boardCopy[i][j]=='r' && gameState==1 || boardCopy[i][j]=='R' && gameState==2)
            {
                for(int k=i;k<8;k++)
                {
                    if(boardCopy[k][j]==king)
                        return 0;
                    if(boardCopy[k][j]!='0')
                        continue;

                }

                for(int k=j;k<8;k++)
                {
                    if(boardCopy[i][k]==king)
                        return 0;
                    if(boardCopy[i][k]!='0')
                        continue;

                }
                for(int k=i;k>=0;k--)
                {
                    if(boardCopy[k][j]==king)
                        return 0;
                    if(boardCopy[k][j]!='0')
                        continue;

                }

                for(int k=j;k>=0;k--)
                {
                    if(boardCopy[i][k]==king)
                        return 0;
                    if(boardCopy[i][k]!='0')
                        continue;

                }


            }

            if(boardCopy[i][j]=='n' && gameState==1 || boardCopy[i][j]=='N' && gameState==2)
            {
                if(boardCopy[i+2][j+1]==king ||boardCopy[i+2][j-1]==king ||boardCopy[i-2][j+1]==king ||boardCopy[i-2][j-1]==king ||
                   boardCopy[i+1][j+2]==king ||boardCopy[i+1][j-2]==king ||boardCopy[i-1][j+2]==king ||boardCopy[i-1][j-2]==king)
                    return 0;
            }

            if(boardCopy[i][j]=='b' && gameState==1 || boardCopy[i][j]=='B' && gameState==2)
                {
                for(int a=i;a<8;a++)
                for(int b=j;b<8;b++)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
                for(int a=i;a<8;a++)
                for(int b=j;b>=0;b--)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
                for(int a=i;a>=0;a--)
                for(int b=j;b<8;b++)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
                for(int a=i;a>=0;a--)
                for(int b=j;b>=0;b--)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }

            }

            if(boardCopy[i][j]=='q' && gameState==1 || boardCopy[i][j]=='Q' && gameState==2)
            {
                for(int k=i;k<8;k++)
                {
                    if(boardCopy[k][j]==king)
                        return 0;
                    if(boardCopy[k][j]!='0')
                        continue;

                }

                for(int k=j;k<8;k++)
                {
                    if(boardCopy[i][k]==king)
                        return 0;
                    if(boardCopy[i][k]!='0')
                        continue;

                }
                for(int k=i;k>=0;k--)
                {
                    if(boardCopy[k][j]==king)
                        return 0;
                    if(boardCopy[k][j]!='0')
                        continue;

                }

                for(int k=j;k>=0;k--)
                {
                    if(boardCopy[i][k]==king)
                        return 0;
                    if(boardCopy[i][k]!='0')
                        continue;

                }
                for(int a=i;a<8;a++)
                for(int b=j;b<8;b++)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
                for(int a=i;a<8;a++)
                for(int b=j;b>=0;b--)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
                for(int a=i;a>=0;a--)
                for(int b=j;b<8;b++)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
                for(int a=i;a>=0;a--)
                for(int b=j;b>=0;b--)
                {
                    if(boardCopy[a][b]==king)
                        return 0;
                    if(boardCopy[a][b]!='0')
                        continue;
                }
            }


            if(boardCopy[i][j]=='p' && gameState==1)
            {
                if(boardCopy[i+1][j+1]==king ||boardCopy[i+1][j-1]==king)
                    return 0;
            }
            if(boardCopy[i][j]=='P' && gameState==2)
            {
                if(boardCopy[i-1][j+1]==king ||boardCopy[i-1][j-1]==king)
                    return 0;
            }

        }
        return 1;
}


void Board::createCopy(int x, int y, int a, int b) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            boardCopy[i][j] = boardState[i][j];

            if (i == x && j == y)
                boardCopy[i][j] = '0';

            if (i == a && j == b)
                boardCopy[i][j] = boardState[x][y];
        }
    }
}