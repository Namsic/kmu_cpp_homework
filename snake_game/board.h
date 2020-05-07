class Board{
private:
    int width, height;
    int **field;
    int head_row, head_col;
    int direction;
    int length;
    int itemProbability[3];
    int itemMaximum[3];
    int itemLife[3];

    void resizeBody(int);
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

    bool setDirection(int);
    bool step();
};
