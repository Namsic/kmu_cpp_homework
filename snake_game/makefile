CC=g++
TARGET=snakeApp.out
OBJS=main.o ui.o board.o

all: $(TARGET)

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lncurses

main.o: board.h ui.h main.cpp
ui.o: board.h ui.h ui.cpp
board.o: board.h board.cpp
