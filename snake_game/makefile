CC=g++
TARGET=snakeApp.exe
OBJS=main.o board.o

all: $(TARGET)

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) -lncurses

main.o: board.h main.cpp
board.o: board.h board.cpp
