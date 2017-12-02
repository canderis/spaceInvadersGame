#include <ncurses.h>
#include <string>

#define X 80
#define Y 21


int doAi = 0;
bool right = true;
char board[X][Y];
bool aiDone[X][Y];

bool ai(int posX, int posY){

    board[posX][posY] = ' ';

    if(right){
        posX++;
    }
    else{
        posX--;
    }

    if(doAi % 2000 == 0){

        if(posY + 1 >= 20)
            return false;
        posY++;
    }
    if (rand() % 100 + 1 == 1){
        board[posX][posY + 1] = '_';
        aiDone[posX][posY + 1] = true;

    }

    board[posX][posY] = 'V';
    aiDone[posX][posY] = true;


    return true;
}

void resetAiBoard(){
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++ ){
            aiDone[i][j] = false;
        }
    }
}

int main(int argc, char *argv[]){
    initscr();                 /* Start curses mode     */
    timeout(1);

    int pcX = 40;
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++ ){
            // if(i > 20 && i < 60 && j == 5 && i % 2 == 0 ){
            //     board[i][j] = 'V';
            // }
            // else if(i > 20 && i < 60 && j == 7 && i % 2 != 0 ){
            //     board[i][j] = 'V';
            //
            // }
            if(i > 20 && i < 60 && j == 9 && i % 2 == 0 ){
                board[i][j] = 'V';

            }
            else if(i == pcX && j == 20){
                board[i][j] = '^';
            }
            else{
                board[i][j] = ' ';
            }
        }
    }
    bool run = true;
    while(run){
        doAi++;
        if(doAi % 1000 == 0){
            right = !right;
        }
        resetAiBoard();

        int key;
        switch (key = getch()) {
            case 'C':
                board[pcX++][20] = ' ';
                board[pcX][20] = '^';
                break;
            case 'D':
                board[pcX--][20] = ' ';
                board[pcX][20] = '^';
                break;
            case 'A': //bullet
                board[pcX][19] = '.';
                break;
            case 'q':
                run = false;
        }
        for(int i = 0; i < X; i++){
            for(int j = 0; j < Y; j++ ){
                if(doAi % 100 == 0){

                    if(board[i][j] == 'V' && !aiDone[i][j]){
                        if(ai(i,j) == false){
                            run = false;
                        }
                    }
                    else if(board[i][j] == '.' ){
                        board[i][j] = ' ';
                        if(j - 1 >= 0){
                            if(board[i][j-1] == 'V')
                                board[i][j-1] = '#';
                            else
                                board[i][j-1] = '.';
                        }
                    }
                    else if(board[i][j] == '_' && !aiDone[i][j] ){
                        aiDone[i][j+1] = true;
                        if(j + 1 <= 20){
                            if(board[i][j+1] != 'V')
                                board[i][j+1] = '_';
                        }
                    }
                    else if(board[i][j] == '#'){
                        board[i][j] = ' ';
                    }

                }


                mvaddch(j, i, board[i][j]);
            }
        }

        refresh();                 /* Print it on to the real screen */
    }
    endwin();                  /* End curses mode    */

    return 0;
}
