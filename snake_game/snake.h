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
    bool on_gate;
    int useItem[3];

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

    int getWidth();
    int getHeight();
    int getField(int, int);
    bool buildWall(int, int, int);

    bool setDirection(int);
    bool step();

    int getElapse();
    int scoreLength();
    int scoreMaxLength();
    int scoreGrowth();
    int scorePoison();
    int scoreGate();
};


// ========== UserInterface Class ========== //
class UserInterface{
private:
    double tick;
    WINDOW *boardWindow;


public:
    UserInterface();
    ~UserInterface();

    void play(Board board, double tick);
};
