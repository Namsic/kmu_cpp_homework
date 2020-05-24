#include "snake.h"

using namespace std;

int main(){
    UserInterface mainUI;

    SnakeGame stage0(30, 30);
    stage0.buildWall(10, 10, 1);
    stage0.buildWall(20, 10, 1);
    stage0.buildWall(10, 20, 1);
    stage0.buildWall(20, 20, 1);

    double t = 0.5;

    mainUI.play(stage0, t);

    return 0;
}
