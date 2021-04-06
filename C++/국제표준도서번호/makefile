CC=g++
OBJS=TestMyISBN.o MyISBN.o

TestMyISBN.out: $(OBJS)
	$(CC) -o $@ $(OBJS)

TestMyISBN.o: MyISBN.h TestMyISBN.cpp
MyISBN.o: MyISBN.h MyISBN.cpp 
