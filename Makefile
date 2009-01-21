CXXFLAGS=-O2 -g
LDFLAGS=-lncurses -g

all: referee random

referee: referee.cpp
	g++ $(CXXFLAGS) -c -o referee.o referee.cpp
	g++ $(LDFLAGS) -o referee referee.o
	rm referee.o

random: random.cpp
	g++ $(CXXFLAGS) -c -o random.o random.cpp
	g++ $(LDFLAGS) -o random random.o
	rm random.o

clean:
	rm referee random
