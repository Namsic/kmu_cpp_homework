#include<cstdlib>
#include<ctime>
#include"snake.h"

// Default constructor
SnakeGame::SnakeGame(){
    srand((unsigned int)time(NULL));
    
    // Default setting
    initMap(21, 21);
    initSnake(height/2, width/2, 1, 3);
    initGrowth(10, 3, 30);
    initPoison(10, 3, 30);
    initGate(10, 2, 30);
    initMission(-1, -1, -1, -1);
}

// Initialize map
void SnakeGame::initMap(int h, int w){
    // Use random size
    if(h < 0) h = rand() % 10 + 21;
    if(w < 0) w = rand() % 10 + 21;

    height = h;
    width = w;

    // Generate empty map
    map = new MapElement*[height];
    for(int i=0; i<height; i++)
        map[i] = new MapElement[width];

    // Generate basic wall
    map[0][0].type = 2;
    map[0][width-1].type = 2;
    map[height-1][0].type = 2;
    map[height-1][width-1].type = 2;

    for(int i=1; i<height-1; i++){
        map[i][0].type = 1;
        map[i][width-1].type = 1;
    }
    for(int i=1; i<width-1; i++){
        map[0][i].type = 1;
        map[height-1][i].type = 1;
    }
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

    map[snake.row][snake.col].type = 3;
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

// Initialize mission
void SnakeGame::initMission(int l, int g, int p, int gate){
    if(l < 0) l = rand() % 5 + 4;
    if(g < 0) g = rand() % 5 + 1;
    if(p < 0) p = rand() % 5 + 1;
    if(gate < 0) gate = rand() % 5 + 1;
    mission.mission_length = l;
    mission.mission_growth = g;
    mission.mission_poison = p;
    mission.mission_gate = gate;
    mission.max_length = 0;
    mission.get_growth = 0;
    mission.get_poison = 0;
    mission.get_gate = 0;
}

// Proceed a tick
bool SnakeGame::step(){
    if(!moveSnake()) return false;

    for(int r=0; r<height; r++)
        for(int c=0; c<height; c++){
            // Reduce MapElement duration
            if(map[r][c].duration > 0 && --map[r][c].duration == 0)
                map[r][c].type = map[r][c].type == 7 ? 1 : 0;
            // Change snake head to body
            if(map[r][c].type == 3){
                map[r][c].type = 4;
                map[r][c].duration = snake.len-1;
            }
        }
    // Draw new head
    map[snake.row][snake.col].type = 3;
    generateItem();
    return true;
}


// Check next space & set next_head
bool SnakeGame::setNextHead(){
    snake.n_r = snake.row;
    snake.n_c = snake.col;
    switch(snake.dir){
    case 0:
        snake.n_r--;
        break;
    case 1:
        snake.n_c--;
        break;
    case 2:
        snake.n_r++;
        break;
    case 3:
        snake.n_c++;
        break;
    }
    
    // Check wall, body and end of map
    if(snake.n_r < 0 || snake.n_r >= height ||
       snake.n_c < 0 || snake.n_c >= width ||
       map[snake.n_r][snake.n_c].type == 1 ||
       map[snake.n_r][snake.n_c].type == 2 ||
       (map[snake.n_r][snake.n_c].type == 4 && 
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
    if(setNextHead() && map[snake.n_r][snake.n_c].type != 7)
        return true;
    // Check clockwise direction(right side)
    snake.dir = (tmp_dir + 3 < 4) ? tmp_dir + 3 : tmp_dir -1;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != 7)
        return true;
    // Check counterclockwise direction(left side)
    snake.dir = (tmp_dir + 1 < 4) ? tmp_dir + 1 : tmp_dir -3;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != 7)
        return true;
    // Check opposite direction(back side)
    snake.dir = (tmp_dir + 2 < 4) ? tmp_dir + 2 : tmp_dir -2;
    if(setNextHead() && map[snake.n_r][snake.n_c].type != 7)
        return true;
    return false;
}

// Move forward one step
bool SnakeGame::moveSnake(){
    // Run into wall or body
    if(!setNextHead()) return false;

    // Pass through a gate
    if(map[snake.n_r][snake.n_c].type == 7){
        // Extend gate duration
        if(map[snake.n_r][snake.n_c].duration < snake.len){
            map[snake.n_r][snake.n_c].duration = snake.len;
            map[map[snake.n_r][snake.n_c].oppo_row]
               [map[snake.n_r][snake.n_c].oppo_col].duration = snake.len;
        }
        if(!enterGate()) return false;
    }

    // Get growth item
    if(map[snake.n_r][snake.n_c].type == 5){ resizeSnake(1); }

    // Get poison item
    if(map[snake.n_r][snake.n_c].type == 6){ resizeSnake(-1); }

    snake.row = snake.n_r;
    snake.col = snake.n_c;
    return true;
}

// Modify snake length
void SnakeGame::resizeSnake(int a){
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(map[r][c].type == 4){
                map[r][c].duration += a;
                if(map[r][c].duration <= 0)
                    map[r][c].type = 0;
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
            case 0:
                empty_cnt++;
                break;
            case 1:
                wall_cnt++;
                break;
            case 5:
            case 6:
            case 7:
                item_cnt[map[r][c].type-5]++;
            }
        }

    // Generate growth item
    if(item_cnt[0] < growth.max && rand()%100 <= growth.pro){
        int index = rand()%empty_cnt;
        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
                if(map[r][c].type == 0 && n++ == index){
                    map[r][c].type = 5;
                    map[r][c].duration = growth.dur;
                }
    }

    // Generate poison item
    if(item_cnt[1] < poison.max && rand()%100 <= poison.pro){
        int index = rand()%empty_cnt;
        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++)
                if(map[r][c].type == 0 && n++ == index){
                    map[r][c].type = 6;
                    map[r][c].duration = poison.dur;
                }
    }

    // Generate gate
    if(item_cnt[2] < gate.max && rand()%100 <= gate.pro){
        int index1, index2;
        int r1, c1, r2, c2;

        index1 = rand()%wall_cnt;
        do{ index2 = rand()%wall_cnt;
        }while(index1 == index2);

        int n = 0;
        for(int r=0; r<height; r++)
            for(int c=0; c<width; c++){
                if(map[r][c].type == 1){
                    if(n == index1){
                        map[r][c].type = 7;
                        map[r][c].duration = gate.dur;
                        r1 = r;
                        c1 = c;
                    }else if(n == index2){
                        map[r][c].type = 7;
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




