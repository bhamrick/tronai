#ifndef NET_H
#define NET_H

#include<list>
#include<cstdio>
#include<cstdilb>
#include<neuron.h>

struct net {
	neuron*** neurons;
	net(int,int*);
	void feed_forward(double*);
	void back_propagate();
	void apply_changes(bool);
};

#endif
