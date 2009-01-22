#ifndef NEURON_H
#define NEURON_H

#include<list>
#include<cmath>
#include<cstdio>
#include<cstdlib>

struct neuron;
struct link;

struct link {
	neuron* n;
	double weight;
};

link mk_link(neuron*,double);

struct neuron {
	std::list<link> blinks;
	double value, bias, deriv, tderiv;
	void feed_forward();
	void add_link(neuron*,double);
	void back_propagate();
	neuron();
};

#endif
