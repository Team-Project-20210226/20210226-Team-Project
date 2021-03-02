#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Да се състави програма, с помощта на която играч може да
играе (с право на връщане на ходовете) следната игра СОЛИТЕР:
На игралното поле са поставени 16 номерирани пулове и три реда
с по осем позиции. Целта е да се извадят от игра всички пулове с
изключение на номер 1. Може да се прескача през някой пул на
свободна клетка, но не се разрешава движение по диагонал.
Например възможни са ходове 1-9; 2-10; 1-2 и т.н. По тази схема 1
прескача 9 и 9х излиза от игра – отстранява се от полето, след
това 2 прескача 10 и 10 отпада от играта; по-нататък 1 прескача 2 и
2 излиза от игра.*/

const int row = 3,col = 8;

char *board[3][8] = {       {"-","-","-","-","-","-","-","-"},
                            {"9","10","11","12","13","14","15","16"},
                            {"1","2","3","4","5","6","7","8"}
};

typedef struct cordinates{
    int col;
    int row;
}cord;

typedef struct userturn{
    cord newturn;
    cord oldturn;
}userTurn;

void menu();
void printBoard();
userTurn* returnPosition(int number);
userTurn* makeMove(userTurn* turn,int move);
int checkMove(userTurn *turn,int move);

int main(void){

    menu();

    return 0;
}

void printBoard(){

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%s\t",board[i][j]);
        }
        printf("\n");
    }

}

void menu(){

    int choice,number,move,validMove,oldNumber;
    userTurn *oldTurn = (userTurn*)malloc(24*sizeof(userTurn));
    userTurn *userNewTurn = (userTurn*)malloc(24*sizeof(userTurn));
    char *numberToString = (char*)malloc(24*20*sizeof(char));
    char *oldNumberToString = (char*)malloc(24*20*sizeof(char));

    menu:
    printBoard(board);
    printf("Menu\n");
    printf("1.Make a turn\n");
    printf("2.Return a turn\n");
    printf("3.Exit\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
        printf("Enter the number you would like to move to: \n");
        scanf("%d",&number);
        oldTurn = returnPosition(number);
        move:
        printf("Choose a way to move:\n");
        printf("1.Up\n");
        printf("2.Down\n");
        printf("3.Left\n");
        printf("4.Right\n");
        scanf("%d",&move);
        if(move == 1){
            oldNumber = atoi(board[oldTurn->oldturn.row][oldTurn->oldturn.col+1]);
        }
        if(move == 2){
            oldNumber = atoi(board[oldTurn->oldturn.row][oldTurn->oldturn.col-1]);
        }
        if(move == 3){
            oldNumber = atoi(board[oldTurn->oldturn.row-1][oldTurn->oldturn.col]);
        }
        if(move == 4){
            oldNumber = atoi(board[oldTurn->oldturn.row+1][oldTurn->oldturn.col]);
        }
        switch(move){
            case 1:
            validMove = checkMove(oldTurn,move);
            if(validMove == 1){
                oldTurn = returnPosition(number);
                userNewTurn = makeMove(oldTurn,move);
                itoa(number,numberToString,10);
                board[oldTurn->oldturn.row][oldTurn->oldturn.col] = "-";
                board[oldTurn->oldturn.row-1][oldTurn->oldturn.col] = "-";
                board[userNewTurn->newturn.row][userNewTurn->newturn.col] = numberToString;
                goto menu;
            }
            else{
                printf("Invalid move!\n");
                goto move;
            }
            break;

            case 2:
            validMove = checkMove(oldTurn,move);
            userNewTurn = makeMove(oldTurn,move);
            if(validMove == 1){
                oldTurn = returnPosition(number);
                itoa(number,numberToString,10);
                board[oldTurn->oldturn.row][oldTurn->oldturn.col] = "-";
                board[oldTurn->oldturn.row+1][oldTurn->oldturn.col] = "-";
                board[userNewTurn->newturn.row][userNewTurn->newturn.col] = numberToString;
                goto menu;
            }
            else{
                printf("Invalid move!\n");
                goto move;
            }
            break;

            case 3:
            validMove = checkMove(oldTurn,move);
            userNewTurn = makeMove(oldTurn,move);
            if(validMove == 1){
                oldTurn = returnPosition(number);
                itoa(number,numberToString,10);
                board[oldTurn->oldturn.row][oldTurn->oldturn.col] = "-";
                board[oldTurn->oldturn.row][oldTurn->oldturn.col-1] = "-";
                board[userNewTurn->newturn.row][userNewTurn->newturn.col] = numberToString;
                goto menu;
            }
            else{
                printf("Invalid move!\n");
                goto move;
            }
            break;

            case 4:
            validMove = checkMove(oldTurn,move);
            userNewTurn = makeMove(oldTurn,move);
            if(validMove == 1){
                oldTurn = returnPosition(number);
                itoa(number,numberToString,10);
                board[oldTurn->oldturn.row][oldTurn->oldturn.col] = "-";
                board[oldTurn->oldturn.row][oldTurn->oldturn.col+1] = "-";
                board[userNewTurn->newturn.row][userNewTurn->newturn.col] = numberToString;
                goto menu;
            }
            else{
                printf("Invalid move!\n");
                goto move;
            }
            break;

            default: 
            printf("Enter a valid number! \n");
            goto move;
        }
        
        case 2:
        itoa(number,numberToString,10);

        itoa(oldNumber,oldNumberToString,10);
        strcpy(board[oldTurn->oldturn.row][oldTurn->oldturn.col],numberToString);
        board[userNewTurn->newturn.row][userNewTurn->newturn.col] = "-";
        if(move == 1){
            strcpy(board[oldTurn->oldturn.row][oldTurn->oldturn.col+1],oldNumberToString);
        }
        if(move == 2){
            strcpy(board[oldTurn->oldturn.row][oldTurn->oldturn.col-1],oldNumberToString);
        }
        if(move == 3){
            strcpy(board[oldTurn->oldturn.row-1][oldTurn->oldturn.col],oldNumberToString);
        }
        if(move == 4){
            strcpy(board[oldTurn->oldturn.row+1][oldTurn->oldturn.col],oldNumberToString);
        }
        break;

        case 3:
        printf("Thank you for playing\n");
        exit(0);
        break;
        
        default:
        printf("Enter a valid choice:\n");
        goto menu;
        break;
    }

}

userTurn* returnPosition(int number){

    userTurn *oldTurn = (userTurn*)malloc(sizeof(userTurn));
    char *numberToString = (char*)malloc(20*sizeof(char));
    itoa(number,numberToString,10);
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(strcmp(board[i][j],numberToString) == 0){
                oldTurn->oldturn.row = i;
                oldTurn->oldturn.col = j;
                return oldTurn;
                break;
            }
        }
    }
}

int checkMove(userTurn *turn,int move){
    
    int i = turn->oldturn.row;
    int j = turn->oldturn.col;
    if(move == 1){
        if(board[i-1][j] != "-" && i >= 0){
            if(board[i-2][j] == "-" && i>= 0){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    if(move == 2){
        if(board[i+1][j] != "-" && i <= row){
            if(board[i+2][j] == "-" && i<= row){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    if(move == 3){
        if(board[i][j-1] != "-" && j >= 0){
            if(board[i][j-2] == "-" && j>=0){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    if(move == 4){
        if(board[i][j+1] != "-" && j <= col){
            if(board[i][j+2] == "-" && j<=col){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
}

userTurn* makeMove(userTurn* turn,int move){

    int i = turn->oldturn.row;
    int j = turn->oldturn.col;

    userTurn *newTurn = (userTurn*)malloc(sizeof(userTurn));

    if(move == 1){
        if(board[i-1][j] != "-" && i >= 0){
            if(board[i-2][j] == "-" && i>=0){
                newTurn->newturn.row = i-2;
                newTurn->newturn.col = j;
                return newTurn;
            }
        }
    }

    if(move == 2){
        if(board[i+1][j] != "-" && i <= row){
            if(board[i+2][j] == "-" && i <= row){
                newTurn->newturn.row = i+2;
                newTurn->newturn.col = j;
                return newTurn;
            }
        }
    }

    if(move == 3){
        if(board[i][j-1] != "-" && j >= 0){
            if(board[i][j-2] == "-" && j>=0){
                newTurn->newturn.row = i;
                newTurn->newturn.col = j-2;
                return newTurn;
            }
        }
    }

    if(move == 4){
        if(board[i][j+1] != "-" && j <= col){
            if(board[i][j+2] == "-" && j <= col){
                newTurn->newturn.row = i;
                newTurn->newturn.col = j+2;
                return newTurn;
            }
        }
    }

}
