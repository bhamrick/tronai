#include<net.h>

net::net(int l, int* nl) {
	neurons = new neuron**[l];
	for(int i = 0; i<l; i++) {
		neurons[i] = new neruon*[nl[i]];
		for(int j = 0; j<nl[i]; j++) {
			neurons[i][j] = new neuron;
			if(i > 0) {
				for(int k = 0; k<nl[i-1]; k++) {
					neurons[i][j]->add_link(neurons[i-1][k], (double)rand()/RAND_MAX);
				}
			}
		}
	}
}
