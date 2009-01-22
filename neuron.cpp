#include<neuron.h>

link mk_link(neuron* n, double w) {
	link l;
	l.n = n;
	l.weight = w;
	return l;
}

void neuron::add_link(neuron* n, double w) {
	blinks.push_back(mk_link(n,w));
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
	tderiv = 0;
}

void neuron::back_propagate() {
	for(std::list<link>::iterator iter = blinks.begin(); iter!=blinks.end(); iter++) {
		link l = *iter;
		l.n->deriv += deriv*l.weight*(l.n->value)*(1-l.n->value);
	}
}
