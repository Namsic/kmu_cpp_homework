#include<ncurses.h>
#include<iostream>
#include<string>
#include "board.h"

using namespace std;

//init_pair(0, COLOR_WHITE, COLOR_BLACK);

int main(){
    Board board;
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_RED);

    WINDOW *boardWindow = 
        newwin(board.getHeight()+1, board.getWidth()*2+1, 1, 2);
    for(int y=0; y<board.getHeight(); y++){
        for(int x=0; x<board.getWidth(); x++){
            wattron(boardWindow, COLOR_PAIR(board.getField(x,y)+1));
            if(board.getField(x,y)==0)
                wprintw(boardWindow, "0 ");
            if(board.getField(x,y)==1)
                wprintw(boardWindow, "1 ");
            if(board.getField(x,y)==2)
                wprintw(boardWindow, "2 ");
            wattroff(boardWindow, COLOR_PAIR(board.getField(x,y)+1));
        }
        wprintw(boardWindow, "\n");
    }
    refresh();
    wrefresh(boardWindow);
    getch();

    delwin(boardWindow);
    endwin();
    return 0;
}
