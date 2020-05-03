class Board{
private:
    int width, height;
    int **field;
    int head_x, head_y;
    int length = 3;
    int direction = 0;

    void reduceBody();
    void growUpBody();


public:
    Board(int = 0);
    int getWidth();
    int getHeight();
    int getField(int, int);

    void setDirection(int);
    bool moveForward();
};
