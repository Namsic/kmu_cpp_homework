CC=g++
OBJS=TestMyIpv4Address.o MyIpv4Address.o

TestMyIpv4Address.out: $(OBJS)
	$(CC) -o $@ $(OBJS)

TestMyIpv4Address.o: MyIpv4Address.h TestMyIpv4Address.cpp
MyIpv4Address.o: MyIpv4Address.h MyIpv4Address.cpp 
