CC=g++
TARGET=snakeApp.out
OBJS=main.o ui.o SnakeGame.o

all: $(TARGET)

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lncurses

main.o: snake.h main.cpp
ui.o: snake.h ui.cpp
SnakeGame.o: snake.h SnakeGame.cpp
