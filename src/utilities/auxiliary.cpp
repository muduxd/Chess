#include <auxiliary.h>


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


void createCopy(int x, int y, int a, int b, char boardState[8][8], char boardCopy[8][8]) {
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


bool kingcheck(int gameState, char boardCopy[8][8]) {

    char king = gameState == 1 ? 'K' : 'k';


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




bool legal(int firstRow, int firstCol, int secondRow, int secondCol, char boardState[8][8], int gameState) {



    if (firstRow == secondRow && firstCol == secondCol) 
        return false;

    if (gameState==2 && (boardState[firstRow][firstCol]>64 && boardState[firstRow][firstCol]<97 
        || boardState[secondRow][secondCol]>97))
        return 0;
    if (gameState==1 && (boardState[firstRow][firstCol]>97 || (boardState[secondRow][secondCol]<97 && boardState[secondRow][secondCol]>64)))
        return 0;

        if(boardState[firstRow][firstCol]=='0')
            return 0;
        
        if(boardState[firstRow][firstCol]=='R' && gameState==1 || boardState[firstRow][firstCol]=='r' && gameState==2)
        {
            if(firstRow==secondRow && firstCol<secondCol)
                for(int i=firstCol+1;i<secondCol;i++)
                if(boardState[firstRow][i]!='0')
                    return 0;
            if(firstRow==secondRow && firstCol>secondCol)
                for(int i=firstCol-1;i>secondCol;i--)
                if(boardState[firstRow][i]!='0')
                    return 0;
            if(firstCol==secondCol && firstRow<secondRow)
                for(int i=firstRow+1;i<secondRow;i++)
                if(boardState[i][firstCol]!='0')
                    return 0;
            if(firstCol==secondCol && firstRow>secondRow)
                for(int i=firstRow-1;i>secondRow;i--)
                if(boardState[i][firstCol]!='0')
                    return 0;
            return 1;
        }
        if(boardState[firstRow][firstCol]=='N' && gameState==1 || boardState[firstRow][firstCol]=='n' && gameState==2)
        {
            if(  (secondRow==firstRow+2 && secondCol==firstCol+1) ||(secondRow==firstRow+2 && secondCol==firstCol-1)
               ||(secondRow==firstRow-2 && secondCol==firstCol+1) ||(secondRow==firstRow-2 && secondCol==firstCol-1)
               ||(secondRow==firstRow+1 && secondCol==firstCol+2) ||(secondRow==firstRow+1 && secondCol==firstCol-2)
               ||(secondRow==firstRow-1 && secondCol==firstCol+2) ||(secondRow==firstRow-1 && secondCol==firstCol-2))
               return 1;
                    
            else return 0;
        }
        if(boardState[firstRow][firstCol]=='B' && gameState==1 || boardState[firstRow][firstCol]=='b' && gameState==2)
        {
            int i=1;
            if(firstRow<secondRow && firstCol<secondCol)
                for(;i<secondRow-firstRow;i++)
                        if(boardState[firstRow+i][firstCol+i]!='0')
                            return 0;
            if(firstRow>secondRow && firstCol>secondCol)
                for(;i<firstRow-secondRow;i++)
                        if(boardState[firstRow-i][firstCol-i]!='0')
                            return 0;
            if(firstRow<secondRow && firstCol>secondCol)
                for(;i<secondRow-firstRow;i++)
                        if(boardState[firstRow+i][firstCol-i]!='0')
                            return 0;
            if(firstRow>secondRow && firstCol<secondCol)
                for(;i<firstRow-secondRow;i++)
                        if(boardState[firstRow-i][firstCol+i]!='0')
                            return 0;
            if(abs(secondRow-firstRow)==i && abs(secondCol-firstCol)==i)
                return 1;
            return 0;
        }
        if(boardState[firstRow][firstCol]=='Q' && gameState==1 || boardState[firstRow][firstCol]=='q' && gameState==2)
        {
            if(firstRow==secondRow && firstCol<secondCol)
                for(int i=firstCol+1;i<secondCol;i++)
                if(boardState[firstRow][i]!='0')
                    return 0;
            if(firstRow==secondRow && firstCol>secondCol)
                for(int i=firstCol-1;i>secondCol;i--)
                if(boardState[firstRow][i]!='0')
                    return 0;
            if(firstCol==secondCol && firstRow<secondRow)
                for(int i=firstRow+1;i<secondRow;i++)
                if(boardState[i][firstCol]!='0')
                    return 0;
            if(firstCol==secondCol && firstRow>secondRow)
                for(int i=firstRow-1;i>secondRow;i--)
                if(boardState[i][firstCol]!='0')
                    return 0;
                    int i=1,ok=0;
            if(firstRow<secondRow && firstCol<secondCol)
                for(ok=1;i<secondRow-firstRow;i++)
                        if(boardState[firstRow+i][firstCol+i]!='0')
                            return 0;
            if(firstRow>secondRow && firstCol>secondCol)
                for(ok=1;i<firstRow-secondRow;i++)
                        if(boardState[firstRow-i][firstCol-i]!='0')
                            return 0;
            if(firstRow<secondRow && firstCol>secondCol)
                for(ok=1;i<secondRow-firstRow;i++)
                        if(boardState[firstRow+i][firstCol-i]!='0')
                            return 0;
            if(firstRow>secondRow && firstCol<secondCol)
                for(ok=1;i<firstRow-secondRow;i++)
                        if(boardState[firstRow-i][firstCol+i]!='0')
                            return 0;
            if(ok)
            if(abs(secondRow-firstRow)==i && abs(secondCol-firstCol)==i)
                return 1;
            else return 0;
            return 1;

        }
        
        if(boardState[firstRow][firstCol]=='P' && gameState==1)
        {
            
            if(secondCol==firstCol)
            if(boardState[secondRow][secondCol]!='0')
            return 0;
            if(secondCol==firstCol)
                if(secondRow!=firstRow-1 && (firstRow!=6 && secondRow==firstRow-2))
                    return 0;

            if((secondCol!=firstCol+1 || secondCol!=firstCol-1) && secondRow!=firstRow-1)
            if(boardState[secondRow][secondCol]!='0')
                return 0;
               
            return 1;
        }
        if(boardState[firstRow][firstCol]=='p' && gameState==2)
        {
            if(secondCol==firstCol)
            if(boardState[secondRow][secondCol]!='0')
            return 0;
            if(secondCol==firstCol)
                if(secondRow!=firstRow+1 && (firstRow!=1 && secondRow==firstRow+2))
                    return 0;

            if((secondCol!=firstCol+1 || secondCol!=firstCol-1) && secondRow!=firstRow+1)
            if(boardState[secondRow][secondCol]!='0')
                return 0;
               
            return 1;
        }

        if(boardState[firstRow][firstCol]=='K' && gameState==1 || boardState[firstRow][firstCol]=='k' && gameState==2)
            if(abs(secondRow-firstRow)>1 || abs(secondCol-firstCol)>1)
                return 0;
            else return 1;

    return true;
}


void RenderState(int gameState, SDL_Renderer *renderer) {

    if (gameState == 1) {
        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
        SDL_Rect rectangle1 { 850, 100, 100, 30 };
        SDL_RenderFillRect(renderer, &rectangle1);


        SDL_SetRenderDrawColor(renderer, grey.r, grey.g, grey.b, grey.a);
        SDL_Rect rectangle2 { 850, 700, 100, 30 };
        SDL_RenderFillRect(renderer, &rectangle2);
    }

    if (gameState == 2) {
        SDL_SetRenderDrawColor(renderer, grey.r, grey.g, grey.b, grey.a);
        SDL_Rect rectangle1 { 850, 100, 100, 30 };
        SDL_RenderFillRect(renderer, &rectangle1);

        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
        SDL_Rect rectangle2 { 850, 700, 100, 30 };
        SDL_RenderFillRect(renderer, &rectangle2);
    }
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