class Board{
private:
    int width;
    int height;
    int **field;
    float tick;

public:
    Board(int w=21, int=21);
    int getWidth();
    int getHeight();
    int getField(int, int);
    bool changeField(int, int, int);
};
