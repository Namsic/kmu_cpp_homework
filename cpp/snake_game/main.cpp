#include "snake.h"

using namespace std;

int main(){
    UserInterface mainUI;
    SnakeGame stage[5];

    // Stage 1(dot)
    stage[0].initMap(21, 21);
    stage[0].buildWall( 5,  5, NORMAL_WALL);
    stage[0].buildWall( 5, 15, NORMAL_WALL);
    stage[0].buildWall(15,  5, NORMAL_WALL);
    stage[0].buildWall(15, 15, NORMAL_WALL);

    // Stage 2(=)
    stage[1].initMap(21, 21);
    stage[2].initMission(-1, -1, -1, -1);
    for(int i=5; i<=15; i++){
        stage[1].buildWall( 5, i, NORMAL_WALL);
        stage[1].buildWall(15, i, NORMAL_WALL);
    }

    // Stage 3(rectangle)
    stage[2].initMap(35, 35);
    stage[2].initMission(-1, -1, -1, -1);
    stage[2].initGateOpen(10, 4);
    for(int i=0; i<5; i++){
        // left_top
        stage[2].buildWall(5+i, 5, NORMAL_WALL);
        stage[2].buildWall(5, 5+i, NORMAL_WALL);
        // right_top
        stage[2].buildWall(5+i, 29, NORMAL_WALL);
        stage[2].buildWall(5, 29-i, NORMAL_WALL);
        // left_bottom
        stage[2].buildWall(29-i, 5, NORMAL_WALL);
        stage[2].buildWall(29, 5+i, NORMAL_WALL);
        // right_bottom
        stage[2].buildWall(29-i, 29, NORMAL_WALL);
        stage[2].buildWall(29, 29-i, NORMAL_WALL);
    }

    // Stage 4(+)
    stage[3].initMap(35, 35);
    stage[3].initMission(-1, -1, -1, -1);
    stage[3].initGateOpen(50, 5);
    for(int i=5; i<=10; i++){
        stage[3].buildWall(17, i, NORMAL_WALL);
        stage[3].buildWall(17, 34-i, NORMAL_WALL);
        stage[3].buildWall(i, 17, NORMAL_WALL);
        stage[3].buildWall(34-i, 17, NORMAL_WALL);
    }

    // Stage 5(<>)
    stage[4].initMap(35, 35);
    stage[4].initMission(-1, -1, -1, -1);
    stage[4].initGateOpen(100, 6);
    for(int i=4; i<14; i++){
        stage[4].buildWall(17-i, i, NORMAL_WALL);
        stage[4].buildWall(17+i, i, NORMAL_WALL);
        stage[4].buildWall(17-i, 34-i, NORMAL_WALL);
        stage[4].buildWall(17+i, 34-i, NORMAL_WALL);
    }

    double start_spd = 0.5;

    int i = 0;
    while(true){
        int res = mainUI.play(stage[i], start_spd);
        if(res == -1)  // Quit
            break;
        // else if(res == 0) retry;
        else if(res == 1){  // Continue
            i++;
            start_spd -= 0.05;
        }
    }

    return 0;
}
