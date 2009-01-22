CXXFLAGS=-O2 -g -I.
LDFLAGS=-lncurses -g

all: referee random netai makeplot

referee: referee.cpp
	g++-4.3.2 $(CXXFLAGS) -c -o referee.o referee.cpp
	g++-4.3.2 $(LDFLAGS) -o referee referee.o
	rm referee.o

random: random.cpp
	g++-4.3.2 $(CXXFLAGS) -c -o random.o random.cpp
	g++-4.3.2 $(LDFLAGS) -o random random.o
	rm random.o

neuron: neuron.cpp neuron.h
	g++-4.3.2 $(CXXFLAGS) -c -o neuron.o neuron.cpp

net: net.cpp net.h
	g++-4.3.2 $(CXXFLAGS) -c -o net.o net.cpp

netai: neuron net netai.cpp
	g++-4.3.2 $(CXXFLAGS) -c -o netai.o netai.cpp
	g++-4.3.2 $(LDFLAGS) -o netai neuron.o net.o netai.o

makeplot: makeplot.cpp
	g++-4.3.2 $(CXXFLAGS) -c -o makeplot.o makeplot.cpp
	g++-4.3.2 $(LDFLAGS) -o makeplot makeplot.o

clean:
	rm referee random *.o netai
