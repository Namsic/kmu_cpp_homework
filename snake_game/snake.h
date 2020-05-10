#include<cstdlib>
#include<ctime>
#include<ncurses.h>

// ========== Board Class ========== //
class Board{
private:
    int elapse;
    int width, height;
    int **field;
    int head_row, head_col;
    int next_row, next_col;
    int direction;
    int length, max_length;
    int itemProbability[3];
    int itemMaximum[3];
    int itemLife[3];
    int gate_open_elapse, gate_open_length;
    bool on_gate;
    int useItem[3];
    int mission[4];
    bool success_mission[4];

    void resizeBody(int);
    bool checkNext(int, int);
    bool enterGate();
    bool moveForward();
    void itemGenerate();


public:
    Board();

    void initMap(int, int);
    void initSnake(int, int, int, int);
    void initItemProbability(int, int, int);
    void initItemMaximum(int, int, int);
    void initItemLife(int, int, int);
    void initGate(int, int);
    void initMission(int, int, int, int);

    int getWidth();
    int getHeight();
    int getField(int, int);
    bool buildWall(int, int, int=1);

    bool setDirection(int);
    bool step();

    int getElapse();
    int scoreLength();
    int scoreMaxLength();
    int scoreGrowth();
    int scorePoison();
    int scoreGate();
    int missionMaxLength();
    int missionGrowth();
    int missionPoison();
    int missionGate();
    int gateOpenElapse();
    int gateOpenLength();
    bool successMaxLength();
    bool successGrowth();
    bool successPoison();
    bool successGate();
};


// ========== UserInterface Class ========== //
class UserInterface{
private:
    double tick;
    WINDOW *boardWindow;
    WINDOW *scoreWindow;
    WINDOW *missionWindow;
    WINDOW *gateWindow;


public:
    UserInterface();
    ~UserInterface();

    bool play(Board board, double tick);
};
