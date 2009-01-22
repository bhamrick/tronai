#include<net.h>

net::net(int l, int* tnl) {
	layers = l;
	nl = new int[l];
	for(int i = 0; i<l; i++) {
		nl[i]=tnl[i];
	}
	neurons = new neuron**[l];
	for(int i = 0; i<l; i++) {
		neurons[i] = new neuron*[nl[i]];
		for(int j = 0; j<nl[i]; j++) {
			neurons[i][j] = new neuron;
			if(i > 0) {
				for(int k = 0; k<nl[i-1]; k++) {
					neurons[i][j]->add_link(neurons[i-1][k], (double)rand()/RAND_MAX-0.5);
				}
			}
		}
	}
}

net::net(char *fname) {
	FILE *fin = fopen(fname,"r");
	fscanf(fin,"%d",&layers);
	nl = new int[layers];
	for(int i = 0; i<layers; i++) {
		fscanf(fin,"%d",&nl[i]);
	}
	for(int i = 1; i<layers; i++) {
		for(int j = 0; j<nl[i]; j++) {
			for(int k = 0; k<nl[i-1]; k++) {
				double v;
				fscanf(fin,"%lf",&v);
				neurons[i][j]->add_link(neurons[i-1][k],v);
			}
			fscanf(fin,"%lf",&neurons[i][j]->bias);
		}
	}
}

void net::feed_forward(double* input) {
	for(int i = 0; i<nl[0]; i++) {
		neurons[0][i]->value = input[i];
	}
	for(int i = 1; i<layers; i++) {
		for(int j = 0; j<nl[i]; j++) {
			neurons[i][j]->feed_forward();
		}
	}
}

void net::back_propagate() {
	
}

void net::apply_changes(bool good) {
	
}

double net::output() {
	return neurons[layers-1][0]->value;
	
}

void net::write_to_file(char *fname) {
	FILE *fout = fopen(fname,"w");
	fprintf(fout,"%d\n",layers);
	fprintf(fout,"%d",nl[0]);
	for(int i = 1; i<layers; i++) {
		fprintf(fout," %d",nl[i]);
	}
	fprintf(fout,"\n");
	for(int i = 1; i<layers; i++) {
		for(int j = 0; j<nl[i]; j++) {
			for(std::list<link>::iterator iter = neurons[i][j]->blinks.begin(); iter!=neurons[i][j]->blinks.end(); iter++) {
				link l = *iter;
				fprintf(fout,"%lf ",l.weight);
			}
			fprintf(fout,"%lf\n",neurons[i][j]->bias);
		}
	}
	fclose(fout);
}
