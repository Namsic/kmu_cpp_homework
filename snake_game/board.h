class Board{
private:
    int width = 21, height = 21;
    int **field;
    int head_row = 10, head_col = 10;
    int direction = 1;
    int length = 3;
    int itemProbability[3] = {5, 5, 5};
    int itemMaximum[3] = {3, 3, 1};
    int itemLife[3] = {20, 20, 50};

    void resizeBody(int);
    bool moveForward();
    void itemGenerate();


public:
    Board(int = 0);
    int getWidth();
    int getHeight();
    int getField(int, int);

    bool setDirection(int);
    bool step();
};
