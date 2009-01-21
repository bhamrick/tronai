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
	double dweight;
	void apply_change();
};

link mk_link(neuron*,double);

struct neuron {
	std::list<link> flinks, blinks;
	double value;
	double bias;
	double deriv;
	void feed_forward();
	void add_link(neuron*,double);
	neuron();
};

#endif
