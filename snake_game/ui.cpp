#include<time.h>
#include<string>
#include "snake.h"

using namespace std;

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


bool UserInterface::play(Board board, double tick){
    tick = tick * CLOCKS_PER_SEC;
    timeout(0);
    int width=board.getWidth();
    int height=board.getHeight();
    wresize(boardWindow, height, width*2+1);
    mvwin(scoreWindow,   1, width*2 + 6);
    mvwin(missionWindow, 8, width*2 + 6);
    mvwin(gateWindow,   14, width*2 + 6);

    erase();
    refresh();
    while(true){
        // Renew score_window
        wmove(scoreWindow, 0, 0);
        wprintw(scoreWindow, " * Score Board *\n  B: ");
        wprintw(scoreWindow, to_string(board.scoreLength()).c_str());
        wprintw(scoreWindow, " / ");
        wprintw(scoreWindow, to_string(board.scoreMaxLength()).c_str());
        wprintw(scoreWindow, "  \n +: ");
        wprintw(scoreWindow, to_string(board.scoreGrowth()).c_str());
        wprintw(scoreWindow, "  \n -: ");
        wprintw(scoreWindow, to_string(board.scorePoison()).c_str());
        wprintw(scoreWindow, "  \n G: ");
        wprintw(scoreWindow, to_string(board.scoreGate()).c_str());
        wprintw(scoreWindow, "  \n E: ");
        wprintw(scoreWindow, to_string(board.getElapse()).c_str());
        wprintw(scoreWindow, "  ");
        wrefresh(scoreWindow);

        // Renew missoin_window
        wmove(missionWindow, 0, 0);
        wprintw(missionWindow, " *   Mission   *\n B: ");
        wprintw(missionWindow, to_string(board.missionMaxLength()).c_str());
        wprintw(missionWindow, " (");
        if(board.successMaxLength()) wprintw(missionWindow, "v)\n +: ");
        else wprintw(missionWindow, " )\n +: ");
        wprintw(missionWindow, to_string(board.missionGrowth()).c_str());
        wprintw(missionWindow, " (");
        if(board.successGrowth()) wprintw(missionWindow, "v)\n -: ");
        else wprintw(missionWindow, " )\n -: ");
        wprintw(missionWindow, to_string(board.missionPoison()).c_str());
        wprintw(missionWindow, " (");
        if(board.successPoison()) wprintw(missionWindow, "v)\n G: ");
        else wprintw(missionWindow, " )\n G: ");
        wprintw(missionWindow, to_string(board.missionGate()).c_str());
        wprintw(missionWindow, " (");
        if(board.successGate()) wprintw(missionWindow, "v)");
        else wprintw(missionWindow, " )");
        wrefresh(missionWindow);

        // Renew gate_window
        wmove(gateWindow, 0, 0);
        wprintw(gateWindow, " *     Gate    *\n E: ");
        wprintw(gateWindow, to_string(board.gateOpenElapse()).c_str());
        wprintw(gateWindow, " (");
        if(board.getElapse() >= board.gateOpenElapse())
            wprintw(gateWindow, "v)\n B: ");
        else wprintw(gateWindow, " )\n B: ");
        wprintw(gateWindow, to_string(board.gateOpenLength()).c_str());
        wprintw(gateWindow, " (");
        if(board.scoreMaxLength() >= board.gateOpenLength())
            wprintw(gateWindow, "v)");
        else wprintw(gateWindow, " )");
        wrefresh(gateWindow);

        // Renew board_window
        wmove(boardWindow, 0, 0);
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
        wrefresh(boardWindow);

        // Input keyboard
        int timeStamp = clock();
        while(clock() - timeStamp < tick){
            switch(getch()){
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
        
        // Check Complete or Fail
        if(!board.step()){
            wattron(boardWindow, COLOR_PAIR(30));
            wmove(boardWindow, height/2-2, width - 9);
            wprintw(boardWindow, "*----------------*");
            wmove(boardWindow, height/2-1, width - 9);
            wprintw(boardWindow, "*-- Game  Over --*");
            wmove(boardWindow, height/2, width - 9);
            wprintw(boardWindow, "*----------------*");
            wmove(boardWindow, height/2+1, width - 9);
            wprintw(boardWindow, "                  ");
            wmove(boardWindow, height/2+2, width - 9);
            wprintw(boardWindow, "Press 'q' to close");
            wrefresh(boardWindow);
            timeout(-1);
            while(getch()!='q');
            return false;
        }
        if( board.successMaxLength() && board.successGrowth() &&
            board.successPoison() && board.successGate() )
        {
            wattron(boardWindow, COLOR_PAIR(20));
            wmove(boardWindow, height/2-2, width - 9);
            wprintw(boardWindow, "*-------------------*");
            wmove(boardWindow, height/2-1, width - 9);
            wprintw(boardWindow, "*------ Clear ------*");
            wmove(boardWindow, height/2, width - 9);
            wprintw(boardWindow, "*-------------------*");
            wmove(boardWindow, height/2+1, width - 9);
            wprintw(boardWindow, "                     ");
            wmove(boardWindow, height/2+2, width - 9);
            wprintw(boardWindow, "Press 'c' to continue");
            wrefresh(boardWindow);
            timeout(-1);
            while(getch()!='c');
            return true;
        }
    }
}

