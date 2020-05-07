#include<time.h>
#include "ui.h"

UserInterface::UserInterface(){
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(10, COLOR_BLACK, COLOR_CYAN);
    init_pair(20, COLOR_BLACK, COLOR_GREEN);
    init_pair(30, COLOR_BLACK, COLOR_RED);
    init_pair(40, COLOR_BLACK, COLOR_MAGENTA);

    boardWindow = newwin(40, 40*2, 1, 2);
}

UserInterface::~UserInterface(){
    delwin(boardWindow);
    endwin();
}

void UserInterface::play(Board board, double tick){
    tick = tick * CLOCKS_PER_SEC;
    int width=board.getWidth();
    int height=board.getHeight();
    refresh();
    bool running = true;
    while(running){
        for(int r=0; r<height; r++){
            for(int c=0; c<width; c++){
                if(board.getField(r,c) > 100)
                    wattron(boardWindow, COLOR_PAIR(board.getField(r,c)/100*10));
                else
                    wattron(boardWindow, COLOR_PAIR(board.getField(r,c)+1));
                wprintw(boardWindow, "  ");
            }
            wprintw(boardWindow, "\n");
        }
        wmove(boardWindow, 0, 0);
        wrefresh(boardWindow);

        int timeStamp = clock();
        while(clock() - timeStamp < tick){
            timeout(0);
            int c = getch();
            switch(c){
                case 'q':
                    running = false;
                break;
                case KEY_UP:
                    board.setDirection(0);
                break;
                case KEY_LEFT:
                    board.setDirection(1);
                break;
                case KEY_DOWN:
                    board.setDirection(2);
                break;
                case KEY_RIGHT:
                    board.setDirection(3);
                break;
            }
        }
        board.step();
    }
}

