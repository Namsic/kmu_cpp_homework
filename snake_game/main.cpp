#include "snake.h"

using namespace std;

int main(){
    UserInterface mainUI;

    Board stage[3];
    double ticks[] = {0.5, 0.5, 0.3};

    // stage_0 setting
    stage[0].initMission(4, 1, 0, 0);

    // stage_1 setting
    stage[1].initMap(30, 25);
    for(int i=5; i<25; i++)
        stage[1].buildWall(i, 12);
    stage[1].initItemLife(30, 30, 60);

    for(int i=0; i<3; i++)
        if(!mainUI.play(stage[i], ticks[i])) break;

    return 0;
}
