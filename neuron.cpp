#include<neuron.h>

void link::apply_change() {
	weight+=dweight;
	dweight = 0;
}

link mk_link(neuron* n, double w) {
	link l;
	l.n = n;
	l.weight = w;
	l.dweight = 0;
	return l;
}

void neuron::add_link(neuron* n, double w) {
	blinks.push_back(mk_link(n,w));
	n->flinks.push_back(mk_link(this,w));
}

void neuron::feed_forward() {
	double sum = bias;
	for(std::list<link>::iterator iter = blinks.begin(); iter != blinks.end(); iter++) {
		link l = *iter;
		sum += l.weight * l.n->value;
	}
	value = 1/(1+exp(-sum));
}

neuron::neuron() {
	value = 0;
	bias = (double)rand()/RAND_MAX - 0.5;
	deriv = 0;
}
