#include<cstdlib>
#include<ctime>
#include"snake.h"

// 생성자
SnakeGame::SnakeGame(int h, int w){
    // rand()의 seed를 현재 시간으로 설정합니다.
    srand((unsigned int)time(NULL));
    // h행 w열의 크기를 갖는 맵을 생성합니다.
    initMap(h, w);

    // 기본값을 설정합니다.
    defaultSetting();
}

// Default setting
void SnakeGame::defaultSetting(){
    initSpeed(0.5);
    initGrowth(10, 3, 30);
    initPoison(10, 3, 30);
    initGate(10, 2, 30);
    initGateOpen(0, 0);
    initMission(-1, -1, -1, -1);

    elapse = 0;
    gate_open = false;
}

// 기본 형태 맵 생성
void SnakeGame::initMap(int h, int w){
    height = h;
    width = w;
    // 비어있는 요소를 height * width 크기로 생성합니다.
    map = new MapElement*[height];
    for(int i=0; i<height; i++)
        map[i] = new MapElement[width];

    // 각 모서리를 IMMUNE_WALL(2)로 변경합니다.
    map[0][0].type = IMMUNE_WALL;
    map[0][width-1].type = IMMUNE_WALL;
    map[height-1][0].type = IMMUNE_WALL;
    map[height-1][width-1].type = IMMUNE_WALL;

    // 바깥쪽을 NORMAL_WALL(1)로 변경합니다.
    for(int i=1; i<height-1; i++){
        map[i][0].type = NORMAL_WALL;
        map[i][width-1].type = NORMAL_WALL;
    }
    for(int i=1; i<width-1; i++){
        map[0][i].type = NORMAL_WALL;
        map[height-1][i].type = NORMAL_WALL;
    }

    // 뱀의 기본값을 설정합니다.
    initSnake(height/2, width/2, DIR_LEFT, 3);
}

// 추가 벽을 생성합니다.
void SnakeGame::buildWall(int r, int c, int t){
    map[r][c].type = t;
}

// 뱀의 기본 위치, 방향, 길이를 설정합니다.
void SnakeGame::initSnake(int r, int c, int d, int l){
    snake.row = r;
    snake.col = c;
    snake.dir = d;
    snake.len = l;

    // 점수를 초기화합니다.
    snake.max_length = snake.len;
    snake.get_growth = 0;
    snake.get_poison = 0;
    snake.get_gate = 0;

    map[snake.row][snake.col].type = SNAKE_HEAD;
}

// 한 틱이 진행되는 시간을 변경합니다.
void SnakeGame::initSpeed(double s){
    tick_speed = s;
}

// Growth 아이템의 설정를 변경합니다.
void SnakeGame::initGrowth(int p, int m, int d){
    growth.pro = p;
    growth.max = m;
    growth.dur = d;
}

// Poison 아이템의 설정를 변경합니다.
void SnakeGame::initPoison(int p, int m, int d){
    poison.pro = p;
    poison.max = m;
    poison.dur = d;
}

// Gate의 설정를 변경합니다.
void SnakeGame::initGate(int p, int m, int d){
    gate.pro = p;
    gate.max = m;
    gate.dur = d;
}

// Gate의 생성 조건을 변경합니다.
void SnakeGame::initGateOpen(int e, int l){
    gate_open_elapse = e;
    gate_open_length = l;
}

// 미션을 변경합니다.
void SnakeGame::initMission(int l, int g, int p, int gate){
    // 인자가 음수인 경우 랜덤으로 설정합니다.
    if(l < 0) l = rand() % 5 + 4;
    if(g < 0) g = rand() % 5 + 1;
    if(p < 0) p = rand() % 5 + 1;
    if(gate < 0) gate = rand() % 5 + 1;

    mission.length = l;
    mission.growth = g;
    mission.poison = p;
    mission.gate = gate;
}

// 한 틱만큼 진행시킵니다.
bool SnakeGame::step(){
    // 뱀이 움직이지 못한 경우 false를 리턴합니다.
    if(!moveSnake()) return false;

    for(int r=0; r<height; r++)
        for(int c=0; c<height; c++){
            // 모든 요소들의 남은 틱수를 1 감소시킵니다.
            // 남은 틱 수가 0인 경우 원래 type으로 변경합니다.
            // 아이템은 0, 게이트는 1
            if(map[r][c].duration > 0 && --map[r][c].duration == 0)
                map[r][c].type = map[r][c].type == GATE ? NORMAL_WALL : EMPTY;
            // 뱀의 head가 있던 자리를 body로 변경합니다.
            if(map[r][c].type == SNAKE_HEAD){
                map[r][c].type = SNAKE_BODY;
                map[r][c].duration = snake.len-1;
            }
        }
    // 진행한 위치의 type을 head로 설정합니다.
    map[snake.row][snake.col].type = SNAKE_HEAD;

    // 아이템을 생성합니다.
    generateItem();

    // 진행한 틱 수를 1 증가시킵니다.
    elapse++;

    // 200틱마다 속도를 증가시킵니다.
    if(elapse % 200 == 0) setTickSpeed(-0.05);

    // 게이트 생성 조건을 만족한 경우 게이트가 생성되기 시작합니다.
    if(elapse >= gate_open_elapse && snake.len >= gate_open_length)
        gate_open = true;

    // 모든 과정이 성공적으로 이루어진 경우 true를 리턴합니다.
    return true;
}

// 틱 진행 속도를 변경합니다.
void SnakeGame::setTickSpeed(double amount){
    // 0.2초보다 적은 값으로는 변경할 수 없습니다.
    if(tick_speed + amount > 0.2)
        tick_speed += amount;
}

// 뱀의 head가 이동할 위치를 설정합니다.
bool SnakeGame::setNextHead(){
    // 현재 뱀의 head 위치를 불러옵니다.
    snake.n_r = snake.row;
    snake.n_c = snake.col;

    // 방향에 따라 다음 위치를 설정합니다.
    switch(snake.dir){
    case DIR_UP:
        snake.n_r--;
        break;
    case DIR_LEFT:
        snake.n_c--;
        break;
    case DIR_DOWN:
        snake.n_r++;
        break;
    case DIR_RIGHT:
        snake.n_c++;
        break;
    }

    // 설정한 위치가 진행 가능한지 확인합니다.
    if(snake.n_r < 0 || snake.n_r >= height ||
       snake.n_c < 0 || snake.n_c >= width ||
       map[snake.n_r][snake.n_c].type == NORMAL_WALL ||
       map[snake.n_r][snake.n_c].type == IMMUNE_WALL ||
       (map[snake.n_r][snake.n_c].type == SNAKE_BODY &&
        map[snake.n_r][snake.n_c].duration > 1))
        return false;
    // 아무런 장애물이 없다면 진행 가능으로 판단합니다.
    return true;
}

// 게이트를 통과합니다.
bool SnakeGame::enterGate(){
    // 뱀의 원래 진행 방향(게이트 진입 방향)을 기억합니다.
    int tmp_dir = snake.dir;

    // 뱀의 head 위치를 반대편 게이트로 변경합니다.
    snake.row = map[snake.n_r][snake.n_c].oppo_row;
    snake.col = map[snake.n_r][snake.n_c].oppo_col;

    // 원래 진행 방향으로 진행이 가능한지 확인합니다.
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // 원래 진행 방향의 시계 방향으로 진행이 가능한지 확인합니다.
    snake.dir = (tmp_dir + 3 < 4) ? tmp_dir + 3 : tmp_dir -1;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // 원래 진행 방향의 반시계 방향으로 진행이 가능한지 확인합니다.
    snake.dir = (tmp_dir + 1 < 4) ? tmp_dir + 1 : tmp_dir -3;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // 원래 진행 방향의 반대 방향으로 진행이 가능한지 확인합니다.
    snake.dir = (tmp_dir + 2 < 4) ? tmp_dir + 2 : tmp_dir -2;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // 4방향 모두 진행이 불가하다면 false를 리턴합니다.
    return false;
}

// 뱀을 한 칸 이동시킵니다.
bool SnakeGame::moveSnake(){
    // 다음 위치로 진행이 가능한지 확인합니다.
    if(!setNextHead()) return false;

    // 게이트를 통과합니다.
    if(map[snake.n_r][snake.n_c].type == GATE){
        // 게이트의 지속시간이 모자랄 경우, 통과할 때 까지 게이트를 유지합니다.
        if(map[snake.n_r][snake.n_c].duration < snake.len){
            map[snake.n_r][snake.n_c].duration = snake.len;
            // 반대편 게이트의 지속시간도 함께 변경합니다.
            map[map[snake.n_r][snake.n_c].oppo_row]
               [map[snake.n_r][snake.n_c].oppo_col].duration = snake.len;
        }
        // 게이트를 통과할 수 없는 경우 이동에 실패합니다.
        if(!enterGate()) return false;
        // 게이트 통과 횟수(미션)을 증가시킵니다.
        snake.get_gate++;
    }

    // Growth 아이템을 획득합니다.
    if(map[snake.n_r][snake.n_c].type == GROWTH){
        // body 길이를 1 증가시킵니다.
        resizeSnake(1);
        // 아이템 획득 횟수(미션)을 증가시킵니다.
        snake.get_growth++;
        // 최대 길이를 갱신합니다.
        if(snake.len > snake.max_length) snake.max_length = snake.len;
    }

    // Poison 아이템을 획득합니다.
    if(map[snake.n_r][snake.n_c].type == POISON){
        // body 길이를 1 감소시킵니다.
        resizeSnake(-1);
        // 아이템 획득 횟수(미션)을 감소시킵니다.
        snake.get_poison++;
        // 몸길이가 3보다 짧은 경우 실패합니다.
        if(snake.len < 3) return false;
    }

    // 뱀의 head를 이동시킵니다.
    snake.row = snake.n_r;
    snake.col = snake.n_c;
    return true;
}

// 뱀의 길이를 변경합니다.
void SnakeGame::resizeSnake(int a){
    // 맵 전체를 탐색합니다.
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            // body의 남은 시간을 늘이거나 줄입니다.
            if(map[r][c].type == SNAKE_BODY){
                map[r][c].duration += a;
                // 남은 시간이 0인 경우 빈 공간으로 되돌립니다.
                if(map[r][c].duration <= 0)
                    map[r][c].type = EMPTY;
            }
        }
    // 길이 변수 값을 변경합니다.
    snake.len += a;
}

// 새로운 아이템과 게이트를 생성합니다.
void SnakeGame::generateItem(){
    // 현재 맵에 있는 아이템과 게이트의 갯수입니다.
    int item_cnt[] = {0, 0, 0};  // {growth, poison, gate}
    // 현재 맵에 있는 빈 공간 갯수와 (게이트 생성 가능한)벽 갯수입니다.
    int empty_cnt = 0, wall_cnt = 0;

    // 각 요소 갯수를 셉니다.
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            switch(map[r][c].type){
            case EMPTY:
                empty_cnt++;
                break;
            case NORMAL_WALL:
                wall_cnt++;
                break;
            case GROWTH:
            case POISON:
            case GATE:
                item_cnt[map[r][c].type-5]++;
            }
        }

    // Growth 아이템을 생성합니다.
    // 현재 갯수가 최대 갯수보다 작고, 생성 확률을 만족한 경우에만 생성합니다.
    if(item_cnt[0] < growth.max && rand()%100 <= growth.pro){
        // index 번째 빈 공간에 아이템을 생성합니다.
        int index = rand()%empty_cnt;
        int n = 0;
        // 맵 전체를 탐색하며
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
                // index번째 빈 공간을 만나면 해당 위치에 아이템을 생성합니다.
                if(map[r][c].type == EMPTY && n++ == index){
                    map[r][c].type = GROWTH;
                    map[r][c].duration = growth.dur;
                }
    }

    // Growth 아이템을 생성합니다.
    // 현재 갯수가 최대 갯수보다 작고, 생성 확률을 만족한 경우에만 생성합니다.
    if(item_cnt[1] < poison.max && rand()%100 <= poison.pro){
        // index 번째 빈 공간에 아이템을 생성합니다.
        int index = rand()%empty_cnt;
        int n = 0;
        // 맵 전체를 탐색하며
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
            // index번째 빈 공간을 만나면 해당 위치에 아이템을 생성합니다.
            if(map[r][c].type == EMPTY && n++ == index){
                    map[r][c].type = POISON;
                    map[r][c].duration = poison.dur;
                }
    }

    // 게이트를 생성합니다.
    // 현재 갯수가 최대 갯수보다 작고, 생성 확률을 만족한 경우에만 생성합니다.
    if(gate_open && item_cnt[2] < gate.max && rand()%100 <= gate.pro){
        // index1번째와 index2번째 빈 공간에 게이트를 생성합니다.
        int index1, index2;
        // 각 게이트의 위치 정보입니다.
        int r1, c1, r2, c2;

        index1 = rand()%wall_cnt;
        // index2는 index1과는 다른 위치를 설정합니다.
        do{ index2 = rand()%wall_cnt;
        }while(index1 == index2);

        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++){
                if(map[r][c].type == NORMAL_WALL){
                  // index1과 index2번째 벽을 만나면 해당 위치에 게이트를 생성합니다.
                  // 생성된 위치를 기억합니다.
                    if(n == index1){
                        map[r][c].type = GATE;
                        map[r][c].duration = gate.dur;
                        r1 = r;
                        c1 = c;
                    }else if(n == index2){
                        map[r][c].type = GATE;
                        map[r][c].duration = gate.dur;
                        r2 = r;
                        c2 = c;
                    }
                    n++;
                }
            }
        // 각 게이트에 반대편 게이트의 위치를 입력합니다.
        map[r1][c1].oppo_row = r2;
        map[r1][c1].oppo_col = c2;
        map[r2][c2].oppo_row = r1;
        map[r2][c2].oppo_col = c1;
    }
}

// 벽을 제외한 모든 요소를 빈 공간으로 되돌립니다.
void SnakeGame::cleanMap(){
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
                if(map[r][c].type > 2){
                    map[r][c].type = map[r][c].type == GATE ? NORMAL_WALL : EMPTY;
                    map[r][c].duration = 0;
                }
}
