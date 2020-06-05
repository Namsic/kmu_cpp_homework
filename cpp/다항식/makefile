CC=g++
OBJS=TestMyPolynomial.o MyTerm.o MyPolynomial.o

TestMyComplex.out: $(OBJS)
	$(CC) -o $@ $(OBJS)

TestMyComplex.o: MyPolynomial.h TestMyComplex.cpp
MyPolynomial.o: MyPolynomial.h MyPolynomial.cpp 
MyTerm.o: MyTerm.h MyTerm.cpp
