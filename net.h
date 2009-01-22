#ifndef NET_H
#define NET_H

#include<list>
#include<cstdio>
#include<cstdlib>
#include<neuron.h>

struct net {
	int layers, *nl;
	neuron*** neurons;
	net(int,int*);
	net(char*);
	void feed_forward(double*);
	void back_propagate();
	void apply_changes(bool);
	double output();
	void write_to_file(char*);
};

#endif
