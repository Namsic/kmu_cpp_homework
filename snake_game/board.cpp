#include<string>
#include<cstdlib>
#include<ctime>
#include "board.h"


// Constructor
Board::Board(){
    srand((unsigned int)time(NULL));
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
}

void Board::initItemProbability(int growth, int poison, int portal){
    itemProbability[0] = growth;
    itemProbability[1] = poison;
    itemProbability[2] = portal;
}

void Board::initItemMaximum(int growth, int poison, int portal){
    itemMaximum[0] = growth;
    itemMaximum[1] = poison;
    itemMaximum[2] = portal;
}

void Board::initItemLife(int growth, int poison, int portal){
    itemLife[0] = growth;
    itemLife[1] = poison;
    itemLife[2] = portal;
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

bool Board::setDirection(int d){
    if(d < 0 || d > 3)
        return false;
    direction = d;
    return true;
}

bool Board::step(){
    for(int r=0; r<height; r++)
        for(int c=0; c<width; c++){
            if(field[r][c] > 100)
                field[r][c] -= 1;
            if(field[r][c]%100 == 0)
                field[r][c] = 0;
        }
    bool res = moveForward();
    itemGenerate();
    return res;
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

bool Board::moveForward(){
    int next_row, next_col;
    switch(direction){
        case 0:  // Up
            next_row = head_row-1;
            next_col = head_col;
        break;
        case 1:  // Left
            next_row = head_row;
            next_col = head_col-1;
        break;
        case 2:  // Down
            next_row = head_row+1;
            next_col = head_col;
        break;
        case 3:  // Right
            next_row = head_row;
            next_col = head_col+1;
        break;
    }

    // Check forward
    if( field[next_row][next_col] == 1 ||
        field[next_row][next_col] == 2 ||
        field[next_row][next_col]/100 == 1 )
        return false;
    
    else if(field[next_row][next_col] == 4)
        resizeBody(+1);
    else if(field[next_row][next_col] == 5)
        resizeBody(-1);
    else if(field[next_row][next_col]/100 == 2)
        resizeBody(+1);
    else if(field[next_row][next_col]/100 == 3)
        resizeBody(-1);

    else if(field[next_row][next_col] == 6)
        return false;
    
    field[head_row][head_col] = 99+length;
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
                case 4:  // portal
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
                    if(field[r][c]==0)
                        n++;
                    if(n == index){
                        field[r][c] = 200 + 100*i + itemLife[i];
                        done = true;
                        break;
                    }
                }
                if(done) break;
            }
        }
    }
}
