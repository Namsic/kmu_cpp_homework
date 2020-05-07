#include <ncurses.h>
#include "board.h"

class UserInterface{
private:
    double tick;
    WINDOW *boardWindow;


public:
    UserInterface();
    ~UserInterface();

    void play(Board board, double tick);
};

