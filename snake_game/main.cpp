#include<ncurses.h>
#include "board.h"

using namespace std;

//init_pair(0, COLOR_WHITE, COLOR_BLACK);

int main(){
    Board board(1);
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_RED);
    init_pair(7, COLOR_BLACK, COLOR_MAGENTA);

    WINDOW *boardWindow = 
        newwin(board.getHeight()+1, board.getWidth()*2+1, 1, 2);

    int running = true;
    while(running){
        for(int y=0; y<board.getHeight(); y++){
            for(int x=0; x<board.getWidth(); x++){
                board.getField(x,y) >= 10 ? 
                    wattron(boardWindow, COLOR_PAIR(7)) : 
                    wattron(boardWindow, COLOR_PAIR(board.getField(x,y)+1));
                if(board.getField(x,y) == 0)
                    wprintw(boardWindow, "0 ");
                else if(board.getField(x,y) == 1)
                    wprintw(boardWindow, "1 ");
                else if(board.getField(x,y) == 2)
                    wprintw(boardWindow, "2 ");
                else if(board.getField(x,y) == 3)
                    wprintw(boardWindow, "3 ");
                else if(board.getField(x,y) == 4)
                    wprintw(boardWindow, "4 ");
                else if(board.getField(x,y) == 5)
                    wprintw(boardWindow, "5 ");
                else
                    wprintw(boardWindow, "9 ");
                wattroff(boardWindow, COLOR_PAIR(board.getField(x,y)+1));
            }
            wprintw(boardWindow, "\n");
        }
        wmove(boardWindow, 0, 0);
        refresh();
        wrefresh(boardWindow);
        
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
            case 'f':
                board.moveForward();
            break;
        }

    }

    delwin(boardWindow);
    endwin();
    return 0;
}
