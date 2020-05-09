CC=g++
TARGET=snakeApp.out
OBJS=main.o ui.o board.o

all: $(TARGET)

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lncurses

main.o: snake.h main.cpp
ui.o: snake.h ui.cpp
board.o: snake.h board.cpp
