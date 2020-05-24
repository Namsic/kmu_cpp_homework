#include<ncurses.h>

// Define constants
const int DIR_UP = 0;
const int DIR_LEFT = 1;
const int DIR_DOWN = 2;
const int DIR_RIGHT = 3;

const int EMPTY = 0;
const int NORMAL_WALL = 1;
const int IMMUNE_WALL = 2;
const int SNAKE_HEAD = 3;
const int SNAKE_BODY = 4;
const int GROWTH = 5;
const int POISON = 6;
const int GATE = 7;

// ==========* SnakeGame Class *========== //
class SnakeGame{
public:
    SnakeGame();
    SnakeGame(int width, int height);
    friend class UserInterface;

    // Initialize game setting
    void buildWall(int row, int col, int wall_type);
    void initSnake(int row, int col, int dir, int len);
    void initGrowth(int probability, int maximum, int duration);
    void initPoison(int probability, int maximum, int duration);
    void initGate(int probability, int maximum, int duration);
    void initGateOpen(int elapse, int length);
    void initMission(int max_length, int growth, int poison, int gate);

private:
    struct MapElement{
        int type;
        int duration;
        // Position of opposite gate
        int oppo_row, oppo_col;
    };
    struct Snake{
        int row, col;  // Position of snake_head
        int n_r, n_c;  // Next_position of snake_head
        int dir;  // Direction of snake_head
        int len;  // Length of snake(head + body)
        int max_length;
        int get_growth;
        int get_poison;
        int get_gate;
    };
    struct Item{
        int pro;  // Generation probability(%)
        int max;  // Maximum existence
        int dur;  // Duration(tick)
    };
    struct Mission{
        int length;
        int growth;
        int poison;
        int gate;
    };

    const int height, width;
    MapElement **map;
    Snake snake;
    Item growth, poison, gate;

    // mission & score
    Mission mission;
    int elapse;
    bool gate_open;
    int gate_open_elapse, gate_open_length;


    void initGame(int height, int width);

    // Control snake
    bool setNextHead();
    bool enterGate();
    bool moveSnake();
    void resizeSnake(int amount);

    bool step();
    void generateItem();
};


// ========== UserInterface Class ========== //
class UserInterface{
private:
    // Define constants
    const int THEME = 5;
    const int VIEW_MARGIN = 8;

    double tick_spd;
    WINDOW *boardWindow;
    WINDOW *scoreWindow;
    WINDOW *missionWindow;
    WINDOW *gateWindow;


public:
    UserInterface();
    ~UserInterface();

    bool play(SnakeGame, double);
};
