#include<string>
#include "board.h"


// Constructor
Board::Board(int stage){
    // Init basic information
    switch(stage){
        case 0:
            width = 21; height = 21;
            head_x = 10; head_y = 10;
        break;
        case 1:
            width = 33; height = 25;
            head_x = 10; head_y = 10;
        break;
    }

    // Generate empty field
    field = new int*[height];
    for(int i=0; i<height; i++)
        field[i] = new int[width];
    for(int y=0;y<height;y++)
        for(int x=0; x<width; x++)
            (y==0 || x==0 || y==height-1 || x==width-1) ? 
            field[y][x] = 1 : field[y][x] = 0;
    field[0][0] = 2; field[height-1][width-1] = 2;
    field[0][width-1] = 2; field[height-1][0] = 2;

    // Generate obstacle
    switch(stage){
        case 1:
            field[3][3] = 4;
            field[15][15] = 5;
        break;
    }

    field[head_y][head_x] = 3;
}

int Board::getWidth(){
    return width;
}
int Board::getHeight(){
    return height;
}

int Board::getField(int x, int y){
    return field[y][x];
}

void Board::setDirection(int d){
    if(d>=0 && d<=3)
        direction = d;
}

bool Board::moveForward(){
    int next_x, next_y;
    // Check forward
    switch(direction){
        case 0: // up
            next_x = head_x;
            next_y = head_y-1;
        break;
        case 1: // left
            next_x = head_x-1;
            next_y = head_y;
        break;
        case 2: // down
            next_x = head_x;
            next_y = head_y+1;
        break;
        case 3: // right
            next_x = head_x+1;
            next_y = head_y;
        break;
    }
    if( field[next_y][next_x] == 1 ||
        field[next_y][next_x] == 2 ||
        field[next_y][next_x] > 10 )
        return false;

    else if(field[next_y][next_x] == 4)
        growUpBody();
    else if(field[next_y][next_x] == 5)
        reduceBody();

    // Contract snake body
    for(int y=0; y<height; y++)
        for(int x=0; x<width; x++){
            if(field[y][x] > 10)
                field[y][x] -= 1;
            else if(field[y][x] == 10)
                field[y][x] = 0;
        }
    field[head_y][head_x] = 8+length;
    head_x = next_x; head_y = next_y;
    field[head_y][head_x] = 3;
    return true;
}

void Board::reduceBody(){
    for(int y=0; y<height; y++)
        for(int x=0; x<width; x++){
            if(field[y][x] > 10)
                field[y][x] -= 1;
            else if(field[y][x] == 10)
                field[y][x] = 0;
        }
    length -= 1;
}

void Board::growUpBody(){
    for(int y=0; y<height; y++)
        for(int x=0; x<width; x++){
            if(field[y][x] > 10)
                field[y][x] -= 1;
            else if(field[y][x] == 10)
                field[y][x] = 0;
        }
    length += 1;
}
