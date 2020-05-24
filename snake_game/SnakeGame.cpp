#include<cstdlib>
#include<ctime>
#include"snake.h"

// Constructor
SnakeGame::SnakeGame(): height(21), width(21){
    initGame(height, width);
}
SnakeGame::SnakeGame(int h, int w): height(h), width(w){
    initGame(height, width);
}

// Initialize basic setting
void SnakeGame::initGame(int h, int w){
    srand((unsigned int)time(NULL));

    // Generate empty map
    map = new MapElement*[height];
    for(int i=0; i<height; i++)
        map[i] = new MapElement[width];

    // Generate basic wall
    map[0][0].type = IMMUNE_WALL;
    map[0][width-1].type = IMMUNE_WALL;
    map[height-1][0].type = IMMUNE_WALL;
    map[height-1][width-1].type = IMMUNE_WALL;

    for(int i=1; i<height-1; i++){
        map[i][0].type = NORMAL_WALL;
        map[i][width-1].type = NORMAL_WALL;
    }
    for(int i=1; i<width-1; i++){
        map[0][i].type = NORMAL_WALL;
        map[height-1][i].type = NORMAL_WALL;
    }

    // Initialize snake
    initSnake(height/2, width/2, DIR_LEFT, 3);

    // Default setting(item & mission)
    initGrowth(10, 3, 30);
    initPoison(10, 3, 30);
    initGate(10, 2, 30);
    initGateOpen(0, 0);
    initMission(-1, -1, -1, -1);

    elapse = 0;
    gate_open = false;
}

// Generate additional wall
void SnakeGame::buildWall(int r, int c, int t){
    map[r][c].type = t;
}

// Initialize snake
void SnakeGame::initSnake(int r, int c, int d, int l){
    snake.row = r;
    snake.col = c;
    snake.dir = d;
    snake.len = l;

    snake.max_length = snake.len;
    snake.get_growth = 0;
    snake.get_poison = 0;
    snake.get_gate = 0;

    map[snake.row][snake.col].type = SNAKE_HEAD;
}

// Initialize growth item
void SnakeGame::initGrowth(int p, int m, int d){
    growth.pro = p;
    growth.max = m;
    growth.dur = d;
}

// Initialize poison item
void SnakeGame::initPoison(int p, int m, int d){
    poison.pro = p;
    poison.max = m;
    poison.dur = d;
}

// Initialize gate
void SnakeGame::initGate(int p, int m, int d){
    gate.pro = p;
    gate.max = m;
    gate.dur = d;
}

// Initialize gate open condition
void SnakeGame::initGateOpen(int e, int l){
    gate_open_elapse = e;
    gate_open_length = l;
}

// Initialize mission
void SnakeGame::initMission(int l, int g, int p, int gate){
    if(l < 0) l = rand() % 5 + 4;
    if(g < 0) g = rand() % 5 + 1;
    if(p < 0) p = rand() % 5 + 1;
    if(gate < 0) gate = rand() % 5 + 1;

    mission.length = l;
    mission.growth = g;
    mission.poison = p;
    mission.gate = gate;
}

// Proceed a tick
bool SnakeGame::step(){
    if(!moveSnake()) return false;

    for(int r=0; r<height; r++)
        for(int c=0; c<height; c++){
            // Reduce MapElement duration
            if(map[r][c].duration > 0 && --map[r][c].duration == 0)
                map[r][c].type = map[r][c].type == GATE ? NORMAL_WALL : EMPTY;
            // Change snake head to body
            if(map[r][c].type == SNAKE_HEAD){
                map[r][c].type = SNAKE_BODY;
                map[r][c].duration = snake.len-1;
            }
        }
    // Draw new head
    map[snake.row][snake.col].type = SNAKE_HEAD;

    generateItem();
    elapse++;
    if(elapse >= gate_open_elapse && snake.len >= gate_open_length)
        gate_open = true;
    return true;
}


// Check next space & set next_head
bool SnakeGame::setNextHead(){
    snake.n_r = snake.row;
    snake.n_c = snake.col;
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
    
    // Check wall, body and end of map
    if(snake.n_r < 0 || snake.n_r >= height ||
       snake.n_c < 0 || snake.n_c >= width ||
       map[snake.n_r][snake.n_c].type == NORMAL_WALL ||
       map[snake.n_r][snake.n_c].type == IMMUNE_WALL ||
       (map[snake.n_r][snake.n_c].type == SNAKE_BODY && 
        map[snake.n_r][snake.n_c].duration > 1))
        return false;
    return true;
}

// Pass gate
bool SnakeGame::enterGate(){
    int tmp_dir = snake.dir;
    snake.row = map[snake.n_r][snake.n_c].oppo_row;
    snake.col = map[snake.n_r][snake.n_c].oppo_col;

    // Check original direction
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // Check clockwise direction(right side)
    snake.dir = (tmp_dir + 3 < 4) ? tmp_dir + 3 : tmp_dir -1;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // Check counterclockwise direction(left side)
    snake.dir = (tmp_dir + 1 < 4) ? tmp_dir + 1 : tmp_dir -3;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    // Check opposite direction(back side)
    snake.dir = (tmp_dir + 2 < 4) ? tmp_dir + 2 : tmp_dir -2;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != GATE)
        return true;
    return false;
}

// Move forward one step
bool SnakeGame::moveSnake(){
    // Run into wall or body
    if(!setNextHead()) return false;

    // Pass through a gate
    if(map[snake.n_r][snake.n_c].type == GATE){
        // Extend gate duration
        if(map[snake.n_r][snake.n_c].duration < snake.len){
            map[snake.n_r][snake.n_c].duration = snake.len;
            map[map[snake.n_r][snake.n_c].oppo_row]
               [map[snake.n_r][snake.n_c].oppo_col].duration = snake.len;
        }
        if(!enterGate()) return false;
        snake.get_gate++;
    }

    // Get growth item
    if(map[snake.n_r][snake.n_c].type == GROWTH){
        resizeSnake(1);
        snake.get_growth++;
        if(snake.len > snake.max_length) snake.max_length = snake.len;
    }

    // Get poison item
    if(map[snake.n_r][snake.n_c].type == POISON){
        resizeSnake(-1);
        snake.get_poison++;
        if(snake.len < 3) return false;
    }

    snake.row = snake.n_r;
    snake.col = snake.n_c;
    return true;
}

// Modify snake length
void SnakeGame::resizeSnake(int a){
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(map[r][c].type == SNAKE_BODY){
                map[r][c].duration += a;
                if(map[r][c].duration <= 0)
                    map[r][c].type = EMPTY;
            }
        }
    snake.len += a;
}

// Generate new item & gate
void SnakeGame::generateItem(){
    int item_cnt[] = {0, 0, 0};  // {growth, poison, gate}
    int empty_cnt = 0, wall_cnt = 0;

    // Count each MapElement_type
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

    // Generate growth item
    if(item_cnt[0] < growth.max && rand()%100 <= growth.pro){
        int index = rand()%empty_cnt;
        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
                if(map[r][c].type == EMPTY && n++ == index){
                    map[r][c].type = GROWTH;
                    map[r][c].duration = growth.dur;
                }
    }

    // Generate poison item
    if(item_cnt[1] < poison.max && rand()%100 <= poison.pro){
        int index = rand()%empty_cnt;
        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
                if(map[r][c].type == EMPTY && n++ == index){
                    map[r][c].type = POISON;
                    map[r][c].duration = poison.dur;
                }
    }

    // Generate gate
    if(gate_open && item_cnt[2] < gate.max && rand()%100 <= gate.pro){
        int index1, index2;
        int r1, c1, r2, c2;

        index1 = rand()%wall_cnt;
        do{ index2 = rand()%wall_cnt;
        }while(index1 == index2);

        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++){
                if(map[r][c].type == NORMAL_WALL){
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
        map[r1][c1].oppo_row = r2;
        map[r1][c1].oppo_col = c2;
        map[r2][c2].oppo_row = r1;
        map[r2][c2].oppo_col = c1;
    }
}




