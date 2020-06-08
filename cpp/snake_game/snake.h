#include<ncurses.h>

// 뱀의 진행 방향입니다.
const int DIR_UP = 0;
const int DIR_LEFT = 1;
const int DIR_DOWN = 2;
const int DIR_RIGHT = 3;

// MapElement의 type입니다.
const int EMPTY = 0;
const int NORMAL_WALL = 1;
const int IMMUNE_WALL = 2;
const int SNAKE_HEAD = 3;
const int SNAKE_BODY = 4;
const int GROWTH = 5;
const int POISON = 6;
const int GATE = 7;


class SnakeGame{
public:
    // 생성자입니다. default는 21 * 21 입니다.
    SnakeGame(int width=21, int height=21);

    // UserInterface에서는 SnakeGame의 다양한 정보를 필요로 하나,
    // 모두 접근자를 만들어 두기에는 양이 지나치게 많고,
    // main 등에서는 public으로 해당 정보에 접근할 필요가 없으므로
    // SnakeGame에서 UserInterface를 friend 선언합니다.
    friend class UserInterface;

    // 게임의 설정을 변경합니다.(수정자에 해당)
    void initMap(int height, int width);
    void buildWall(int row, int col, int wall_type);
    void initSnake(int row, int col, int dir, int len);
    void initSpeed(double speed);
    void initGrowth(int probability, int maximum, int duration);
    void initPoison(int probability, int maximum, int duration);
    void initGate(int probability, int maximum, int duration);
    void initGateOpen(int elapse, int length);
    void initMission(int max_length, int growth, int poison, int gate);

private:
    // 맵의 각 요소입니다.
    struct MapElement{
        int type;  // 무엇이 있는지를 나타냅니다.
        int duration;  // 사라질 때 까지 남은 시간(틱) 입니다.
        int oppo_row, oppo_col;  // 반대편 게이트의 위치입니다.
    };
    struct Snake{
        int row, col;  // 뱀의 현재 머리 위치입니다.
        int n_r, n_c;  // 다음 틱에 머리가 이동할 위치입니다.
        int dir;  // 진행 방향입니다.
        int len;  // 몸 길이입니다.
        int max_length;  // 가장 길었을 때 길이입니다.
        int get_growth;  // 획득한 Growth 아이템 수입니다.
        int get_poison;  // 획득한 Poison 아이템 수입니다.
        int get_gate;  // 통과한 게이트 수입니다.
    };
    struct Item{
        int pro;  // 생성 확률(%) 입니다.
        int max;  // 동시 존재 가능 최대 개수입니다.
        int dur;  // 지속시간입니다.
    };
    struct Mission{
        int length;
        int growth;
        int poison;
        int gate;
    };

    int height, width;  // 맵 크기입니다.
    MapElement **map;  // 게임 맵입니다.
    Snake snake;  // 플레이어가 조종할 수 있는 뱀입니다.
    Item growth, poison, gate;  // 각 아이템 및 게이트에 대한 정보를 갖습니다.

    // 기본값으로 설정합니다.
    void defaultSetting();

    // mission & score
    Mission mission;
    // 게임 시작 후 진행한 틱 수입니다.
    int elapse;
    // 1틱이 진행되는 데 걸리는 시간(초) 입니다.
    double tick_speed;
    // 게이트 생성 조건 만족 여부입니다.
    bool gate_open;
    // 게이트 생성 조건입니다.
    int gate_open_elapse, gate_open_length;


    bool setNextHead();
    bool enterGate();
    bool moveSnake();
    void resizeSnake(int amount);

    bool step();
    void setTickSpeed(double amount);
    void generateItem();
    void cleanMap();
};


class UserInterface{
private:
    // 기본 배경색입니다.
    const int THEME = 5;
    // 화면 이동 시 여유 공간입니다.
    // 적은 값을 사용할 수록 화면 바깥쪽까지 다가가야 화면이 이동됩니다.
    const int VIEW_MARGIN = 8;

    double tick_spd;
    WINDOW *boardWindow;
    WINDOW *scoreWindow;
    WINDOW *missionWindow;
    WINDOW *gateWindow;


public:
    UserInterface();
    ~UserInterface();

    int play(SnakeGame);
};
