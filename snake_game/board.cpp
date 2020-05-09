#include<cstdlib>
#include<ctime>
#include "snake.h"


// Constructor
Board::Board(){
    srand((unsigned int)time(NULL));
    elapse = 0;
    on_gate = false;
    for(int i=0; i<3; i++)
        useItem[i] = 0;
    // Default Setting
    initMap(21, 21);
    initSnake(10, 10, 1, 3);
    initItemProbability(5, 5, 5);
    initItemMaximum(3, 3, 1);
    initItemLife(20, 20, 20);

    // Generate empty field
    field = new int*[height];
    for(int i=0; i<height; i++)
        field[i] = new int[width];
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++)
            (r==0 || c==0 || r==height-1 || c==width-1) ? 
            field[r][c] = 1 : field[r][c] = 0;
    field[0][0] = 2; field[height-1][width-1] = 2;
    field[0][width-1] = 2; field[height-1][0] = 2;
}


void Board::initMap(int w, int h){
    width = w;
    height = h;
}
void Board::initSnake(int r, int c, int d, int l){
    head_row = r;
    head_col = c;
    direction = d;
    length = l;
    max_length = length;
}
void Board::initItemProbability(int growth, int poison, int gate){
    itemProbability[0] = growth;
    itemProbability[1] = poison;
    itemProbability[2] = gate;
}
void Board::initItemMaximum(int growth, int poison, int gate){
    itemMaximum[0] = growth;
    itemMaximum[1] = poison;
    itemMaximum[2] = gate;
}
void Board::initItemLife(int growth, int poison, int gate){
    itemLife[0] = growth;
    itemLife[1] = poison;
    itemLife[2] = gate;
}

int Board::getWidth(){
    return width;
}
int Board::getHeight(){
    return height;
}
int Board::getField(int r, int c){
    return field[r][c];
}
bool Board::buildWall(int r, int c, int type){
    if(type != 1 && type != 2)
        return false;
    if(r < 0 || r >= height || c < 0 || c >= width)
        return false;
    field[r][c] = type;
    return true;
}

bool Board::setDirection(int d){
    if(d < 0 || d > 3)
        return false;
    direction = d;
    return true;
}

bool Board::step(){
    if(!moveForward()) return false;
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(field[r][c] > 100)
                field[r][c] -= 1;
            if(field[r][c]%100 == 0){
                if(field[r][c] == 400){
                    field[r][c] = 1;
                }
                else field[r][c] = 0;
            }
        }
    //if(length < 3) return false;
    itemGenerate();
    elapse++;
    return true;
}

int Board::getElapse(){
    return elapse;
}
int Board::scoreLength(){
    return length;
}
int Board::scoreMaxLength(){
    return max_length;
}
int Board::scoreGrowth(){
    return useItem[0];
}
int Board::scorePoison(){
    return useItem[1];
}
int Board::scoreGate(){
    return useItem[2];
}

void Board::resizeBody(int amount){
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(field[r][c]/100 == 1)
                field[r][c] += amount;
            if(field[r][c] == 100)
                field[r][c] = 0;
        }
    length += amount;
}

bool Board::enterGate(){
    int p_row, p_col;
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(field[r][c]/100 == 4){
                if(field[r][c] < 400+length)
                    field[r][c] = 400+length;
                if(r != next_row || c != next_col){
                    p_row = r;
                    p_col = c;
                }
            }
        }

    int origin_d = direction;
    if(checkNext(p_row, p_col) && field[next_row][next_col]/100 != 4)
        return true;

    direction = origin_d+3 < 4 ? origin_d+3 : origin_d-1;
    if(checkNext(p_row, p_col) && field[next_row][next_col]/100 != 4)
        return true;

    direction = origin_d+1 < 4 ? origin_d+1 : origin_d-3;
    if(checkNext(p_row, p_col) && field[next_row][next_col]/100 != 4)
        return true;

    direction = origin_d+2 < 4 ? origin_d+2 : origin_d-2;
    if(checkNext(p_row, p_col) && field[next_row][next_col]/100 != 4)
        return true;
    return false;
}

bool Board::checkNext(int base_row, int base_col){
    switch(direction){
        case 0:  // Up
            next_row = base_row-1;
            next_col = base_col;
        break;
        case 1:  // Left
            next_row = base_row;
            next_col = base_col-1;
        break;
        case 2:  // Down
            next_row = base_row+1;
            next_col = base_col;
        break;
        case 3:  // Right
            next_row = base_row;
            next_col = base_col+1;
        break;
    }

    if( next_row < 0 || next_row >= height ||
        next_col < 0 || next_col >= width ||
        field[next_row][next_col] == 1 ||
        field[next_row][next_col] == 2 ||
        (field[next_row][next_col]/100 == 1 && field[next_row][next_col]!=101 )
        )
        return false;
    return true;
}

bool Board::moveForward(){
    if(!checkNext(head_row, head_col))
        return false;
    else if(field[next_row][next_col]/100 == 4){
        if(!enterGate())
            return false;
        useItem[2]++;
    }
    else if(field[next_row][next_col]/100 == 2){
        resizeBody(+1);
        useItem[0]++;
        if(length > max_length)
            max_length = length;
    }
    else if(field[next_row][next_col]/100 == 3){
        resizeBody(-1);
        useItem[1]++;
    }

    field[head_row][head_col] = 100+length;
    head_row = next_row;
    head_col = next_col;
    field[head_row][head_col] = 3;
    return true;
}

void Board::itemGenerate(){
    int itemCount[3] = {0, 0, 0};
    int emptyCount = 0, wallCount = 0;

    // Count item
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(field[r][c] == 0)
                emptyCount++;
            else if(field[r][c] == 1)
                wallCount++;
            switch(field[r][c]/100){
                case 2:  // growth item
                case 3:  // poison item
                case 4:  // gate
                    itemCount[field[r][c]/100 - 2]++;
                break;
            }
        }

    // Generate growth/reduce item
    for(int i=0; i<2; i++){
        if(itemCount[i] < itemMaximum[i] && rand()%100 <= itemProbability[i]){
            int index = rand()%emptyCount;
            int n = 0;
            bool done = false;
            for(int r=0; r<height; r++){
                for(int c=0; c<width; c++){
                    if(field[r][c]==0){
                        n++;
                        if(n == index){
                            field[r][c] = 200 + 100*i + itemLife[i];
                            done = true;
                            break;
                        }
                    }
                }
                if(done) break;
            }
        }
    }
    // Generate gate
    if(!on_gate) return;
    if(itemCount[2] < itemMaximum[2] && rand()%100 <= itemProbability[2]){
        int index1, index2;
        index1 = rand()%(wallCount);
        do{
            index2 = rand()%(wallCount);
        }while(index1 == index2);

        int n=0;
        bool done1=false, done2=false;
        for(int r=0; r<height; r++){
            for(int c=0; c<width; c++){
                if(field[r][c] == 1){
                    n++;
                    if(!done1 && n == index1){
                        field[r][c] = 400 + itemLife[2];
                        done1 = true;
                    }
                    if(!done2 && n == index2){
                        field[r][c] = 400 + itemLife[2];
                        done2 = true;
                    }
                    if(done1 && done2) break;
                }
            }
            if(done1 && done2) break;
        }
    }
}
