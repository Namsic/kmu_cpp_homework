#include<time.h>
#include<string>
#include "snake.h"

using namespace std;

UserInterface::UserInterface(){
    // ncurses에서 필요한 초기 설정입니다.
    initscr();
    // 키보드 입력을 화면에 표시하지 않습니다.
    noecho();
    // 커서를 표시하지 않습니다.
    curs_set(FALSE);
    // 키보드 방향키 사용을 위함입니다.
    keypad(stdscr, TRUE);
    // 색을 사용합니다.
    start_color();

    // 각 요소에 맞는 색을 설정합니다.
    init_pair(1, COLOR_BLACK, COLOR_WHITE);  // empty
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // normal wall
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  // immune wall
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);  // snake head
    init_pair(5, COLOR_BLACK, COLOR_CYAN);  // snake body
    init_pair(6, COLOR_BLACK, COLOR_GREEN);  // growth item
    init_pair(7, COLOR_BLACK, COLOR_RED);  // poison item
    init_pair(8, COLOR_BLACK, COLOR_MAGENTA);  // gate

    // 각 window의 크기와 위치를 설정합니다.
    boardWindow = newwin(21, 21*2+1, 1, 2);
    scoreWindow   = newwin(7, 17,  1, 21*2+6);
    missionWindow = newwin(5, 17,  9, 21*2+6);
    gateWindow    = newwin(5, 17, 15, 21*2+6);

    // 각 윈도우의 배경색을 설정합니다.
    bkgd(COLOR_PAIR(THEME));
    wbkgd(boardWindow, COLOR_PAIR(THEME));
    wbkgd(scoreWindow, COLOR_PAIR(2));
    wbkgd(missionWindow, COLOR_PAIR(2));
    wbkgd(gateWindow, COLOR_PAIR(2));

    // 각 윈도우의 텍스트 색을 설정합니다.
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


// 게임을 플레이합니다.
int UserInterface::play(SnakeGame game){
    // 현재 맵 위의 요소를 지웁니다.
    game.cleanMap();
    // 키보드 입력을 기다리지 않습니다.
    timeout(0);

    // 미션 클리어 여부입니다.
    bool mission[4] = {false, false, false, false};

    refresh();
    // 화면에 보일 부분 좌표입니다.(좌측 상단 기준)
    int view_r = 0, view_c = 0;
    while(true){
        // 뱀의 머리가 화면 아래쪽으로 이동할 경우, 화면을 아래쪽으로 이동합니다.
        if(game.snake.row >= view_r + 21 - VIEW_MARGIN)
            while( view_r < game.height - 21 &&
                   game.snake.row >= view_r + 21 - VIEW_MARGIN)
                view_r++;
        // 뱀의 머리가 화면 위쪽으로 이동할 경우, 화면을 위쪽으로 이동합니다.
        else if(game.snake.row < view_r + VIEW_MARGIN)
            while( view_r > 0 &&
                   game.snake.row < view_r + VIEW_MARGIN )
                view_r--;

        // 뱀의 머리가 화면 오른쪽으로 이동할 경우, 화면을 오른쪽으로 이동합니다.
        if(game.snake.col >= view_c + 21 - VIEW_MARGIN)
            while( view_c < game.width - 21 &&
                   game.snake.col >= view_c + 21 - VIEW_MARGIN)
                view_c++;
        // 뱀의 머리가 화면 왼쪽으로 이동할 경우, 화면을 왼쪽으로 이동합니다.
        else if(game.snake.col < view_c + VIEW_MARGIN)
            while( view_c > 0 &&
                   game.snake.col < view_c + VIEW_MARGIN )
                view_c--;

        // 게임 화면을 새로 그립니다.
        // 게임 화면의 왼쪽 위부터 새로 작성합니다.
        wmove(boardWindow, 0, 0);
        // 21*21만큼 화면에 표시합니다.
        for(int r=0; r<21; r++){
            for(int c=0; c<21; c++){
                // 해당 위치의 type에 맞는 색을 설정합니다.
                wattron(boardWindow, COLOR_PAIR(
                    game.map[view_r + r][view_c + c].type+1
                ));
                // 위 색을 갖는 공백을 2칸 작성합니다.
                wprintw(boardWindow, "  ");
            }
            // 한 행이 끝난 경우 줄을 바꿉니다.
            wprintw(boardWindow, "\n");
        }
        // 작성한 내용을 새로 반영합니다.
        wrefresh(boardWindow);

        // 점수판을 새로 작성합니다.
        // 좌측 위로 커서를 이동합니다.
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

        // 미션 진행 상황을 새로 그립니다.
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

        // 게이트 생성 조건 상황을 새로 그립니다.
        wmove(gateWindow, 0, 0);
        wprintw(gateWindow, " *    Gate     *");
        wprintw(gateWindow, game.gate_open ?
            "\n - Gate opened -\n >: " : "\n - Gate closed -\n >: ");
        wprintw(gateWindow, to_string(game.gate_open_elapse).c_str());
        wprintw(gateWindow, "\n ~: ");
        wprintw(gateWindow, to_string(game.gate_open_length).c_str());
        wrefresh(gateWindow);


        int time_check = clock();
        // 틱이 진행되는 사이에는 계속해서 입력을 받습니다.
        while(clock() - time_check < game.tick_speed * CLOCKS_PER_SEC)
            // 키보드 입력에 따라 방향을 변경하거나 게임을 중단합니다.
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
            // 게임을 재시작합니다.(main에서 처리)
            case 'r':
                return 0;
                break;
            // 게임을 종료합니다.(main에서 처리)
            case 'q':
                return -1;
                break;
            }

        // 게임이 진행되지 못했습니다.(뱀 이동 실패)
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
            // 사용자 입력을 기다립니다.
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
        // 모든 미션을 성공했는지 확인합니다.
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

        // 미션 성공 여부를 갱신합니다.
        if(game.snake.len >= game.mission.length) mission[0] = true;
        if(game.snake.get_growth >= game.mission.growth) mission[1] = true;
        if(game.snake.get_poison >= game.mission.poison) mission[2] = true;
        if(game.snake.get_gate >= game.mission.gate) mission[3] = true;
    }
}
