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

    boardWindow = newwin(21, 21*2+1, 1, 2);
    scoreWindow   = newwin(7, 17,  1, 21*2+6);
    missionWindow = newwin(5, 17,  9, 21*2+6);
    gateWindow    = newwin(5, 17, 15, 21*2+6);

    bkgd(COLOR_PAIR(THEME));
    wbkgd(boardWindow, COLOR_PAIR(THEME));
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


int UserInterface::play(SnakeGame game){
    game.cleanMap();
    timeout(0);

    bool mission[4] = {false, false, false, false};

    refresh();
    int view_r = 0, view_c = 0;
    while(true){
        // Move view point
        if(game.snake.row >= view_r + 21 - VIEW_MARGIN)
            while( view_r < game.height - 21 &&
                   game.snake.row >= view_r + 21 - VIEW_MARGIN)
                view_r++;
        else if(game.snake.row < view_r + VIEW_MARGIN)
            while( view_r > 0 && 
                   game.snake.row < view_r + VIEW_MARGIN )
                view_r--;

        if(game.snake.col >= view_c + 21 - VIEW_MARGIN)
            while( view_c < game.width - 21 &&
                   game.snake.col >= view_c + 21 - VIEW_MARGIN)
                view_c++;
        else if(game.snake.col < view_c + VIEW_MARGIN)
            while( view_c > 0 && 
                   game.snake.col < view_c + VIEW_MARGIN )
                view_c--;

        // Renew board_window
        wmove(boardWindow, 0, 0);
        for(int r=0; r<21; r++){
            for(int c=0; c<21; c++){
                wattron(boardWindow, COLOR_PAIR(
                    game.map[view_r + r][view_c + c].type+1
                ));
                wprintw(boardWindow, "  ");
            }
            wprintw(boardWindow, "\n");
        }
        wrefresh(boardWindow);

        // Renew score_window
        wmove(scoreWindow, 0, 0);
        wprintw(scoreWindow, " * Score board *\n >: ");
        wprintw(scoreWindow, to_string(game.elapse).c_str());
        wprintw(scoreWindow, "\n ~: ");
        wprintw(scoreWindow, to_string(game.snake.len).c_str());
        wprintw(scoreWindow, "\n +: ");
        wprintw(scoreWindow, to_string(game.snake.get_growth).c_str());
        wprintw(scoreWindow, "\n -: ");
        wprintw(scoreWindow, to_string(game.snake.get_poison).c_str());
        wprintw(scoreWindow, "\n *: ");
        wprintw(scoreWindow, to_string(game.snake.get_gate).c_str());
        wprintw(scoreWindow, "\n tick speed: ");
        wprintw(scoreWindow, to_string(game.tick_speed).c_str());
        wrefresh(scoreWindow);

        // Renew mission_window
        wmove(missionWindow, 0, 0);
        wprintw(missionWindow, " *   Mission   *");
        wprintw(missionWindow, mission[0] ? "\n ~(v): " : "\n ~( ): ");
        wprintw(missionWindow, to_string(game.mission.length).c_str());
        wprintw(missionWindow, mission[1] ? "\n +(v): " : "\n +( ): ");
        wprintw(missionWindow, to_string(game.mission.growth).c_str());
        wprintw(missionWindow, mission[2] ? "\n -(v): " : "\n -( ): ");
        wprintw(missionWindow, to_string(game.mission.poison).c_str());
        wprintw(missionWindow, mission[3] ? "\n *(v): " : "\n *( ): ");
        wprintw(missionWindow, to_string(game.mission.gate).c_str());
        wrefresh(missionWindow);

        // Renew gate_window
        wmove(gateWindow, 0, 0);
        wprintw(gateWindow, " *    Gate     *");
        wprintw(gateWindow, game.gate_open ?
            "\n - Gate opened -\n *: " : "\n - Gate closed -\n ~: ");
        wprintw(gateWindow, to_string(game.gate_open_elapse).c_str());
        wprintw(gateWindow, "\n ~: ");
        wprintw(gateWindow, to_string(game.gate_open_length).c_str());
        wrefresh(gateWindow);

        // Input keboard
        int time_check = clock();
        while(clock() - time_check < game.tick_speed * CLOCKS_PER_SEC)
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
            case 'r':
                return 0;
                break;
            case 'q':
                return -1;
            }

        // Fail
        if(!game.step()){
            wattron(boardWindow, COLOR_PAIR(7));
            wmove(boardWindow, 8, 12);
            wprintw(boardWindow, "*----------------*");
            wmove(boardWindow, 9, 12);
            wprintw(boardWindow, "*-- Game  Over --*");
            wmove(boardWindow, 10, 12);
            wprintw(boardWindow, "*----------------*");
            wmove(boardWindow, 11, 12);
            wprintw(boardWindow, "                  ");
            wmove(boardWindow, 12, 12);
            wprintw(boardWindow, "Press 'r' to retry");
            wmove(boardWindow, 13, 12);
            wprintw(boardWindow, "Press 'q' to close");
            wrefresh(boardWindow);
            timeout(-1);
            while(true){
                int c = getch();
                if(c == 'r'){
                    return 0;
                }
                else if(c == 'q')
                    return -1;
            }
        }
        // Success
        if(mission[0] && mission[1] && mission[2] && mission[3]){
            wattron(boardWindow, COLOR_PAIR(6));
            wmove(boardWindow, 8, 11);
            wprintw(boardWindow, "*-------------------*");
            wmove(boardWindow, 9, 11);
            wprintw(boardWindow, "*------ Clear ------*");
            wmove(boardWindow, 10, 11);
            wprintw(boardWindow, "*-------------------*");
            wmove(boardWindow, 11, 11);
            wprintw(boardWindow, "                     ");
            wmove(boardWindow, 12, 11);
            wprintw(boardWindow, "Press 'c' to continue");
            wrefresh(boardWindow);
            timeout(-1);
            while(getch()!='c');
            return 1;
        }

        // Renew mission status
        if(game.snake.len >= game.mission.length) mission[0] = true;
        if(game.snake.get_growth >= game.mission.growth) mission[1] = true;
        if(game.snake.get_poison >= game.mission.poison) mission[2] = true;
        if(game.snake.get_gate >= game.mission.gate) mission[3] = true;
    }
}

