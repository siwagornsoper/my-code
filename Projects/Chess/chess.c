#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Piece{
    char type; /*K is king N is knight Q is queen B is bishop R is rook P is pawn 0 is an empty tile*/
    char color; /*0 for white 1 for black*/
    char firstMove;
};

/*tests whether a move is a valid up left diagonal move*/
int testUpLeft(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX - 1;
    j = prevY + 1;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(i < 0 || j > 7)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        i--;
        j++;
    }

    /*if you reach the intended square without issues then it's an up left diagonal valid move*/
    return 1;
}

int testUp(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX;
    j = prevY + 1;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(j > 7)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        j++;
    }

    /*if you reach the intended square without issues then it's an up valid move*/
    return 1;
}

int testUpRight(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX + 1;
    j = prevY + 1;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(i > 7 || j > 7)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        i++;
        j++;
    }

    /*if you reach the intended square without issues then it's an up right diagonal valid move*/
    return 1;
}

int testRight(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX + 1;
    j = prevY;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(i > 7)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        i++;
    }

    /*if you reach the intended square without issues then it's a right valid move*/
    return 1;
}

int testDownRight(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX + 1;
    j = prevY - 1;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(i > 7 || j < 0)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        i++;
        j--;
    }

    /*if you reach the intended square without issues then it's a down right diagonal valid move*/
    return 1;
}

int testDown(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX;
    j = prevY - 1;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(j < 0)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        j--;
    }

    /*if you reach the intended square without issues then it's a down valid move*/
    return 1;
}

int testDownLeft(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX - 1;
    j = prevY - 1;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(i < 0 || j < 0)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        i--;
        j--;
    }

    /*if you reach the intended square without issues then it's an down left diagonal valid move*/
    return 1;
}

int testLeft(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int i;
    int j;

    i = prevX - 1;
    j = prevY;

    while(i != newX || j != newY){
        /*if out of bounds return false*/
        if(i < 0)
            return 0;

        /*if there's any pieces leading up to the end of the diagonal return false*/
        if(board[i][j].type)
            return 0;

        i--;
    }

    /*if you reach the intended square without issues then it's an left valid move*/
    return 1;
}

/*is this a valid pawn move?*/
int validPawn(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    if(board[prevX][prevY].color){ /*black pawn*/
        /*diagonal capture is possible if a white piece is present*/
        if(newY == prevY + 1 && (newX == prevX - 1 || newX == prevX + 1) && !board[newX][newY].color && board[newX][newY].type){
            board[prevX][prevY].firstMove = 0;
            
            return 1;
        } /*if the piece is moving forward and nothing is in front of it*/
        else if(newY == prevY + 1 && newX == prevX && !board[newX][newY].type){
            board[prevX][prevY].firstMove = 0;
            
            return 1;
        }/*if going forwards by two, make sure it's the first move and there's no pieces in the way*/
        else if(newY == prevY + 2 && newX == prevX && !board[newX][newY].type && !board[prevX][prevY+1].type && board[prevX][prevY].firstMove){
            board[prevX][prevY].firstMove = 0;
            
            return 1;
        }
    }
    else{ /*white pawn*/
        /*diagonal capture is possible if a black piece is present*/
        if(newY == prevY - 1 && (newX == prevX - 1 || newX == prevX + 1) && board[newX][newY].color && board[newX][newY].type){
            board[prevX][prevY].firstMove = 0;
            
            return 1;
        } /*if the piece is moving forward and nothing is in front of it*/
        else if(newY == prevY - 1 && newX == prevX && !board[newX][newY].type){
            board[prevX][prevY].firstMove = 0;

            return 1;
        }/*if going forwards by two, make sure it's the first move and there's no pieces in the way*/
        else if(newY == prevY - 2 && newX == prevX && !board[newX][newY].type && !board[prevX][prevY-1].type && board[prevX][prevY].firstMove){
            board[prevX][prevY].firstMove = 0;
            
            return 1;
        }
    }

    return 0;
}

/*is this a valid bishop move?*/
int validBishop(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    /*false if a piece is attacking its own color*/
    if(board[newX][newY].type && (board[newX][newY].color == board[prevX][prevY].color)){
        return 0;
    }

    if(testUpLeft(board, prevX, prevY, newX, newY))
        return 1;


    if(testUpRight(board, prevX, prevY, newX, newY))
        return 1;


    if(testDownRight(board, prevX, prevY, newX, newY))
        return 1;


    if(testDownLeft(board, prevX, prevY, newX, newY))
        return 1;
    
    return 0;
}

/*is this a valid rook move?*/
int validRook(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    /*false if a piece is attacking its own color*/
    if(board[newX][newY].type && (board[newX][newY].color == board[prevX][prevY].color)){
        return 0;
    }
    
    if(testUp(board, prevX, prevY, newX, newY))
        return 1;


    if(testRight(board, prevX, prevY, newX, newY))
        return 1;


    if(testDown(board, prevX, prevY, newX, newY))
        return 1;


    if(testLeft(board, prevX, prevY, newX, newY))
        return 1;

    return 0;
}

/*is this a valid queen move?*/
int validQueen(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    /*false if a piece is attacking its own color*/
    if(board[newX][newY].type && (board[newX][newY].color == board[prevX][prevY].color)){
        return 0;
    }

    if(testUp(board, prevX, prevY, newX, newY))
        return 1;


    if(testRight(board, prevX, prevY, newX, newY))
        return 1;


    if(testDown(board, prevX, prevY, newX, newY))
        return 1;


    if(testLeft(board, prevX, prevY, newX, newY))
        return 1;


    if(testUpLeft(board, prevX, prevY, newX, newY))
        return 1;


    if(testUpRight(board, prevX, prevY, newX, newY))
        return 1;


    if(testDownRight(board, prevX, prevY, newX, newY))
        return 1;


    if(testDownLeft(board, prevX, prevY, newX, newY))
        return 1;
    
    return 0;
}

/*is this a valid knight move?*/
int validKnight(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int xDiff;
    int yDiff;
    
    /*false if a piece is attacking its own color*/
    if(board[newX][newY].type && (board[newX][newY].color == board[prevX][prevY].color)){
        return 0;
    }

    xDiff = abs(newX - prevX);
    yDiff = abs(newY - prevY);

    if((xDiff == 1 && yDiff == 2) || (xDiff == 2 && yDiff == 1))
        return 1;
    
    return 0;
}

/*is this a valid king move?*/
int validKing(struct Piece board[8][8], int prevX, int prevY, int newX, int newY){
    int xDiff;
    int yDiff;
    
    /*false if a piece is attacking its own color*/
    if(board[newX][newY].type && (board[newX][newY].color == board[prevX][prevY].color)){
        return 0;
    }
    
    xDiff = abs(newX-prevX);
    yDiff = abs(newY-prevY);

    if(xDiff != 0 && xDiff != 1)
        return 0;

    if(yDiff != 0 && yDiff != 1)
        return 0;

    return 1;
}

/*determines if a player's own king was placed in danger as a result of a move*/
int kingDanger(struct Piece board[8][8], int colorTurn){
    int i;
    int j;

    int kingX;
    int kingY;
    
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(board[i][j].type == 'K' && board[i][j].color == colorTurn){
                kingX = i;
                kingY = j;
                break;
            } 
        }
    }

    i = kingX + 2;

    /*2 enemy knight checks*/
    if(i < 8){
        j = kingY + 1;

        if(j < 8){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }

        j = kingY - 1;

        if(j >= 0){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }
    }

    i = kingX - 2;

    /*2 enemy knight checks*/
    if(i >= 0){
        j = kingY + 1;

        if(j < 8){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }

        j = kingY - 1;

        if(j >= 0){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }
    }

    i = kingX + 1;

    /*2 enemy knight checks*/
    if(i < 8){
        j = kingY + 2;

        if(j < 8){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }

        j = kingY - 2;

        if(j >= 0){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }
    }

    i = kingX - 1;

    /*2 enemy knight checks*/
    if(i >= 0){
        j = kingY + 2;

        if(j < 8){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }

        j = kingY - 2;

        if(j >= 0){
            if(board[i][j].type == 'N' && board[i][j].color != colorTurn)
                return 1;
        }
    }

    j = kingY;
    /*rook/queen check*/
    for(i = kingX + 1; i < 8; i++){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'R' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }
    }

    /*rook/queen check*/
    for(i = kingX - 1; i >= 0; i--){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'R' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }
    }

    i = kingX;
    /*rook/queen check*/
    for(j = kingY + 1; j < 8; j++){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'R' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }
    }

    /*rook/queen check*/
    for(j = kingY - 1; j >= 0; j--){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'R' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }
    }

    /*bishop/queen check*/
    i = kingX + 1;
    j = kingY + 1;
    while(i < 8 && j < 8){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'B' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }

        i++;
        j++;
    }

    /*bishop/queen check*/
    i = kingX - 1;
    j = kingY - 1;
    while(i >= 0 && j >= 0){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'B' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }

        i--;
        j--;
    }

    /*bishop/queen check*/
    i = kingX + 1;
    j = kingY - 1;
    while(i < 8 && j >= 0){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'B' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }

        i++;
        j--;
    }

    /*bishop/queen check*/
    i = kingX - 1;
    j = kingY + 1;
    while(i >= 0 && j < 8){
        if(board[i][j].type != 0){
            if(board[i][j].color != colorTurn && (board[i][j].type == 'B' || board[i][j].type == 'Q'))
                return 1;
            else
                break;
        }

        i--;
        j++;
    }

    /*pawn check*/
    if(colorTurn){ /*if black*/
        j = kingY + 1;

        if(j < 8){
            i = kingX + 1;

            if(i < 8){
                if(board[i][j].type == 'P' && board[i][j].color != colorTurn)
                    return 1;
            }

            i = kingX - 1;
            
            if(i >= 0){
                if(board[i][j].type == 'P' && board[i][j].color != colorTurn)
                    return 1;
            }
        }
    }
    else{
        j = kingY - 1;

        if(j >= 0){
            i = kingX + 1;

            if(i < 8){
                if(board[i][j].type == 'P' && board[i][j].color != colorTurn)
                    return 1;
            }

            i = kingX - 1;
            
            if(i >= 0){
                if(board[i][j].type == 'P' && board[i][j].color != colorTurn)
                    return 1;
            }
        }
    }

    i = kingX + 1;

    /*king check*/
    if(i < 8){
        if(board[i][kingY].type == 'K')
            return 1;

        j = kingY - 1;

        if(j >= 0 && board[i][j].type == 'K')
            return 1;

        j = kingY + 1;

        if(j < 8 && board[i][j].type == 'K')
            return 1;
    }

    i = kingX - 1;

    /*king check*/
    if(i >= 0){
        if(board[i][kingY].type == 'K')
            return 1;

        j = kingY - 1;

        if(j >= 0 && board[i][j].type == 'K')
            return 1;

        j = kingY + 1;

        if(j < 8 && board[i][j].type == 'K')
            return 1;
    }

    j = kingY - 1;

    /*king check*/
    if(j >= 0 && board[kingX][j].type == 'K')
        return 1;

    j = kingY + 1;

    /*king check*/
    if(j < 8 && board[kingX][j].type == 'K')
        return 1;

    return 0;
}

/*moves a piece from one place to another given the move is proper and then outputs if the move was successful*/
int move(struct Piece board[8][8], int prevX, int prevY, int newX, int newY, int colorTurn){
    struct Piece empty;
    struct Piece placeHolder;
    empty.type = 0;
    empty.color = 0;

    if(board[prevX][prevY].color != colorTurn){
        if(colorTurn){
            printf("it isn't white's turn");
        }
        else{
            printf("it isn't black's turn");
        }
        return 0;
    }

    /*each case represents one piece type. based on the piece type conditions are checked*/
    switch(board[prevX][prevY].type){
        case 'K':
            if(!validKing(board, prevX, prevY, newX, newY)){
                printf("Invalid king move");
                return 0;
            }
            break;
        case 'Q':
            if(!validQueen(board, prevX, prevY, newX, newY)){
                printf("Invalid queen move");
                return 0;
            }
            break;
        case 'R':
            if(!validRook(board, prevX, prevY, newX, newY)){
                printf("Invalid rook move");
                return 0;
            }
            break;
        case 'B':
            if(!validBishop(board, prevX, prevY, newX, newY)){
                printf("Invalid bishop move");
                return 0;
            }
            break;
        case 'N':
            if(!validKnight(board, prevX, prevY, newX, newY)){
                printf("Invalid knight move");
                return 0;
            }
            break;
        case 'P':
            if(!validPawn(board, prevX, prevY, newX, newY)){
                printf("Invalid pawn move");
                return 0;
            }
            break;
        default:
            return 0;
    }

    /*saves the captured piece and moves the chosen piece*/
    placeHolder = board[newX][newY];
    board[newX][newY] = board[prevX][prevY];
    board[prevX][prevY] = empty;

    /*king danger check*/
    if(kingDanger(board, colorTurn)){
        /*if king is in jeopardy, undo the move and report the unsuccessful move*/
        board[prevX][prevY] = board[newX][newY];
        board[newX][newY] = placeHolder;
        printf("That move puts the king in danger");

        return 0;
    }

    return 1;
}

/*creates a proper chess setup*/
void createBoard(struct Piece board[8][8]){
    int i;
    int j;
    int isBlack;

    isBlack = 1;

    for(j=0; j<8; j+=7){
        board[0][j].type = 'R';
        board[1][j].type = 'N';
        board[2][j].type = 'B';
        board[3][j].type = 'Q';
        board[4][j].type = 'K';
        board[5][j].type = 'B';
        board[6][j].type = 'N';
        board[7][j].type = 'R';

        for(i=0; i<8; i++){
            board[i][j].color = isBlack;
            board[i][j].firstMove = 1;
        }

        isBlack = !isBlack;
    }

    for(j=1; j<8; j+=5){
        for(i=0; i<8; i++){
            board[i][j].type = 'P';
            board[i][j].color = isBlack;
            board[i][j].firstMove = 1;
        }

        isBlack = !isBlack;
    }

    for(j=2; j<6; j++){
        for(i=0; i<8; i++){
            board[i][j].type = 0;
        }
    }
}


void printBoard(struct Piece board[8][8]){
    int i;
    int j;
    int coord;
    
    coord = 8;

    printf("\n");

    for(j=0; j<8; j++){
        printf("%i    ", coord);
        
        for(i=0; i<8; i++){
            if(board[i][j].type){
                if(board[i][j].color){
                    printf("b");
                }
                else{
                    printf("w");
                }
                printf("%c ",board[i][j].type);
            }
            else
                printf("## ");
        }
        printf("\n");

        coord--;
    }

    printf("\n     a  b  c  d  e  f  g  h\n");
}

/*converts the string into coordinates, moves the piece if the move is proper, then outputs if the move was successful*/
int stringMove(struct Piece board[8][8], char* string, int colorTurn){
    int coord1;
    int coord2;
    int coord3;
    int coord4;

    coord1 = string[0] - 97;
    coord2 = 7 - string[1] + 49;
    coord3 =string[3] - 97;
    coord4 = 7 - string[4] + 49;

    if(coord1 > 7 || coord2 > 7 || coord3 > 7 || coord4 > 7 || coord1 < 0 || coord2 < 0 || coord3 < 0 || coord4 < 0){
        printf("invalid coords\n");
    }
    
    return move(board, coord1, coord2, coord3, coord4, colorTurn);
}

int main(int argc, char** argv){
    struct Piece board[8][8];
    char coordIO[6];
    char c;
    int colorTurn;

    colorTurn = 0; /*white's turn first*/

    createBoard(board);

    printBoard(board);


    while(1){
        fgets(coordIO, 6, stdin);

        if(stringMove(board, coordIO, colorTurn))
            colorTurn = !colorTurn;

        printBoard(board);

        /*clears stdin*/
        while((c = fgetc(stdin)) != EOF && c != '\n');
    }
    

    return 0;
}