CC=g++
OBJS=TestMyComplex.o MyComplex.o

TestMyComplex.out: $(OBJS)
	$(CC) -o $@ $(OBJS)

TestMyComplex.o: MyComplex.h TestMyComplex.cpp
MyComplex.o: MyComplex.h MyComplex.cpp 
