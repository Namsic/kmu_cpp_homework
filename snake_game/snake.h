#include<ncurses.h>

// ==========* SnakeGame Class *========== //
class SnakeGame{
public:
    SnakeGame();
    friend class UserInterface;

    // Initialize game setting
    void initMap(int height, int width);
    void buildWall(int row, int col, int wall_type);
    void initSnake(int row, int col, int dir, int len);
    void initGrowth(int probability, int maximum, int duration);
    void initPoison(int probability, int maximum, int duration);
    void initGate(int probability, int maximum, int duration);
    void initMission(int max_length, int growth, int poison, int gate);

private:
    struct MapElement{
        int type;
        /* Type_Code
         * 0: empty
         * 1: normal wall
         * 2: immune wall
         * 3: snake_head
         * 4: snake_body
         * 5: growth item
         * 6: poison item
         * 7: gate
         */
        int duration;
        /* Duration Code
         * -1: infinite
         *  0: empty
         * +n: disappear affter n ticks
         */
        // Position of opposite gate
        int oppo_row, oppo_col;
    };
    struct Snake{
        int row, col;  // Position of snake_head
        int n_r, n_c;  // Next_position of snake_head
        int dir;
        /* Direction_Code
         * 0: Up
         * 1: Left
         * 2: Down
         * 3: Right
         */
        int len;  // Length of snake_body + 1(head)
    };
    struct Item{
        int pro;  // Generation probability(%)
        int max;  // Maximum existence
        int dur;  // Duration(tick)
    };
    struct Mission{
        mission_length;
        mission_growth;
        mission_poison;
        mission_gate;
        max_length;
        get_growth;
        get_poison;
        get_gate;
    };
    int height, width;
    MapElement **map;
    Snake snake;
    Item growth, poison, gate;
    Mission mission;

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
