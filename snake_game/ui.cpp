#include<time.h>
#include<string>
#include "snake.h"

using namespace std;

UserInterface::UserInterface(){
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    start_color();

    // Initialize color code
    init_pair(1, COLOR_BLACK, COLOR_WHITE);  // empty
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // normal wall
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // immune wall
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);  // snake head
    init_pair(5, COLOR_BLACK, COLOR_CYAN);  // snake body
    init_pair(6, COLOR_BLACK, COLOR_GREEN);  // growth item
    init_pair(7, COLOR_BLACK, COLOR_RED);  // poison item
    init_pair(8, COLOR_BLACK, COLOR_MAGENTA);  // gate
    bkgd(COLOR_PAIR(1));

    boardWindow = newwin(21, 21*2+1, 1, 2);
    scoreWindow   = newwin(6, 17, 1, 2);
    missionWindow = newwin(5, 17, 1, 2);
    gateWindow    = newwin(5, 17, 1, 2);

    wbkgd(boardWindow, COLOR_PAIR(1));
    wbkgd(scoreWindow, COLOR_PAIR(2));
    wbkgd(missionWindow, COLOR_PAIR(2));
    wbkgd(gateWindow, COLOR_PAIR(2));

    wattron(scoreWindow, COLOR_PAIR(2));
    wattron(missionWindow, COLOR_PAIR(2));
    wattron(gateWindow, COLOR_PAIR(2));
}

UserInterface::~UserInterface(){
    delwin(boardWindow);
    delwin(scoreWindow);
    delwin(missionWindow);
    endwin();
}


bool UserInterface::play(SnakeGame game, double tick){
    tick_spd = tick * CLOCKS_PER_SEC;
    timeout(0);
    wresize(boardWindow, game.height, game.width*2+1);
    mvwin(scoreWindow,   1, game.width*2 + 6);
    mvwin(missionWindow, 8, game.width*2 + 6);
    mvwin(gateWindow,   14, game.width*2 + 6);

    erase();
    refresh();
    while(true){
        // Renew board_window
        wmove(boardWindow, 0, 0);
        for(int r=0; r<game.height; r++){
            for(int c=0; c<game.width; c++){
                wattron(boardWindow, COLOR_PAIR(game.map[r][c].type+1));
                wprintw(boardWindow, "  ");
            }
            wprintw(boardWindow, "\n");
        }
        wrefresh(boardWindow);

        // Input keboard
        int time_check = clock();
        while(clock() - time_check < tick_spd)
            switch(getch()){
            case KEY_UP:
                game.snake.dir = 0;
                break;
            case KEY_LEFT:
                game.snake.dir = 1;
                break;
            case KEY_DOWN:
                game.snake.dir = 2;
                break;
            case KEY_RIGHT:
                game.snake.dir = 3;
                break;
            }
        if(!game.step()) break;
    }
    return true;
}

