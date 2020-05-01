#include "board.h"

// Constructor
Board::Board(int w, int h){
    width = w;
    height = h;
    tick = 0.5;

    // Generate field
    field = new int*[height];
    for(int i=0; i<height; i++)
        field[i] = new int[width];

    // Init field
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            (i==0 || j==0 || i==height-1 || j==width-1) ?
                field[i][j] = 1 : field[i][j] = 0;
    field[0][0] = 2; field[0][width-1] = 2;
    field[height-1][0] = 2; field[height-1][width-1] = 2;
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

bool Board::changeField(int x, int y, int v){
    if(x<0 || x>=width || y<0 || y>=height)
        return false;
    field[y][x] = v;
    return true;
}

