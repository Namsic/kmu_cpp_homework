#include<time.h>
#include<ncurses.h>
#include "board.h"

using namespace std;

//init_pair(0, COLOR_WHITE, COLOR_BLACK);

int main(){
    double tick = 0.5 * CLOCKS_PER_SEC;
    Board board(1);
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(10, COLOR_BLACK, COLOR_CYAN);
    init_pair(20, COLOR_BLACK, COLOR_GREEN);
    init_pair(30, COLOR_BLACK, COLOR_RED);
    init_pair(40, COLOR_BLACK, COLOR_MAGENTA);

    WINDOW *boardWindow = 
        newwin(board.getHeight()+1, board.getWidth()*2+1, 1, 2);

    int running = true;
    while(running){
        for(int r=0; r<board.getHeight(); r++){
            for(int c=0; c<board.getWidth(); c++){
                if(board.getField(r,c) > 100)
                    wattron(boardWindow, COLOR_PAIR(board.getField(r,c)/100*10));
                else
                    wattron(boardWindow, COLOR_PAIR(board.getField(r,c)+1));
                wprintw(boardWindow, "  ");
                if(board.getField(r,c) > 100)
                    wattroff(boardWindow, COLOR_PAIR(board.getField(r,c)/100+3));
                else
                    wattroff(boardWindow, COLOR_PAIR(board.getField(r,c)+1));
            }
            wprintw(boardWindow, "\n");
        }
        wmove(boardWindow, 0, 0);
        refresh();
        wrefresh(boardWindow);
        
        int timeStamp = clock();
        while(clock()-timeStamp<tick){
            timeout(0);
            int c = getch();
            switch(c){
                case 'q':
                    running = false;
                break;
                case 'w':
                    board.setDirection(0);
                break;
                case 'a':
                    board.setDirection(1);
                break;
                case 's':
                    board.setDirection(2);
                break;
                case 'd':
                    board.setDirection(3);
                break;
            }
        }
        board.step();

    }

    delwin(boardWindow);
    endwin();
    return 0;
}
