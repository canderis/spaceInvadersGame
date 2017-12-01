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
        mvaddstr(21, 5, std::to_string(doAi).c_str());

        if(posY + 1 >= 20)
            return false;
        posY++;
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
            if(i > 20 && i < 60 && j > 5 && j < 10 && ( (i % 2 == 0 && j % 2 == 0) ) ){
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
                    else if(board[i][j] == '*' ){
                        board[i][j] = ' ';
                        if(j + 1 >= 20){
                            if(board[i][j-1] == '^')
                                board[i][j-1] = '#';
                            else
                                board[i][j-1] = '*';
                        }
                    }
                    else if(board[i][j] == '#'){
                        board[i][j] = ' ';
                    }
                }
                if(doAi % 327 == 0 && board[i][j] == ' ' && j - 1 >= 0 && board[i][j-1] == 'V'){
                    board[i][j] = '*';
                    doAi++;
                }

                mvaddch(j, i, board[i][j]);
            }
        }

        refresh();                 /* Print it on to the real screen */
    }
    endwin();                  /* End curses mode    */

    return 0;
}
