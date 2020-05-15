#include "snake.h"

using namespace std;

int main(){
    UserInterface mainUI;

    SnakeGame stage[3];
    double ticks[] = {0.5, 0.5, 0.3};

    // stage_0 setting

    // stage_1 setting
    mainUI.play(stage[0], ticks[0]);

    return 0;
}
