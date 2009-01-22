#include<net.h>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<neuron.h>

using namespace std;

int main() {
	printf("NETAI\n");
	fflush(stdout);
	srand(time(NULL)*getpid());
	char opp[21];
	scanf("%s",opp);
	int w, h, x1, x2, y1, y2;
	bool** board;
	scanf("%d%d",&w,&h);
	board = new bool*[w];
	for(int i = 0; i<w; i++) {
		board[i] = new bool[h];
		for(int j = 0; j<h; j++) board[i][j] = 0;
	}
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	board[x1][y1] = board[x2][y2] = 1;
	int layers = 3;
	int nl[3]={w*h,(int)(5+w*h*log(w*h)),1};
	char working_name[30];
	sprintf(working_name,"%s%d%d.wk",opp,w,h);
	net n(layers,nl);
	FILE *fin = fopen(working_name,"r");
	if(fin != NULL) {
		fclose(fin);
		n = net(working_name);
	}
	while(1) {
		double * input;
		double nv, ev, sv, wv;
		if(y1 < h-1 && !board[x1][y1+1]) {
			input = new double[w*h];
			board[x1][y1+1]=1;
			for(int i = 0; i<w; i++) {
				for(int j = 0; j<h; j++) {
					input[i*h+j]=0.5*(double)(int)board[i][j];
				}
			}
			input[x1*h+y1+1]=1;
			n.feed_forward(input);
			delete[] input;
			nv = n.output();
			board[x1][y1+1]=0;
		} else {
			nv = -1;
		}
		if(x1 < w-1 && !board[x1+1][y1]) {
			input = new double[w*h];
			board[x1+1][y1]=1;
			for(int i = 0; i<w; i++) {
				for(int j = 0; j<h; j++) {
					input[i*h+j]=0.5*(double)(int)board[i][j];
				}
			}
			input[(x1+1)*h+y1]=1;
			n.feed_forward(input);
			delete[] input;
			ev = n.output();
			board[x1+1][y1]=0;
		} else {
			ev = -1;
		}
		if(y1 > 0 && !board[x1][y1-1]) {
			input = new double[w*h];
			board[x1][y1-1]=1;
			for(int i = 0; i<w; i++) {
				for(int j = 0; j<h; j++) {
					input[i*h+j]=0.5*(double)(int)board[i][j];
				}
			}
			input[x1*h+y1-1]=1;
			n.feed_forward(input);
			delete[] input;
			sv = n.output();
			board[x1][y1-1]=0;
		} else {
			sv = -1;
		}
		if(x1 > 0 && !board[x1-1][y1]) {
			input = new double[w*h];
			board[x1-1][y1]=1;
			for(int i = 0; i<w; i++) {
				for(int j = 0; j<h; j++) {
					input[i*h+j]=0.5*(double)(int)board[i][j];
				}
			}
			input[(x1-1)*h+y1]=1;
			n.feed_forward(input);
			delete[] input;
			wv = n.output();
			board[x1-1][y1]=0;
		} else {
			wv = -1;
		}
		fprintf(stderr,"%lf %lf %lf %lf\n",nv,ev,sv,wv);
		char bestmove = 'N';
		double bestval = nv;
		if(ev > bestval) {
			bestmove = 'E';
			bestval = ev;
		}
		if(wv > bestval) {
			bestmove = 'W';
			bestval = wv;
		}
		if(sv > bestval) {
			bestmove = 'S';
			bestval = sv;
		}

		if(bestmove=='N') {
			y1++;
			board[x1][y1]=1;
		} else if(bestmove=='E') {
			x1++;
			board[x1][y1]=1;
		} else if(bestmove=='S') {
			y1--;
			board[x1][y1]=1;
		} else if(bestmove=='W') {
			x1--;
			board[x1][y1]=1;
		}
		input = new double[w*h];
		for(int i = 0; i<w; i++) {
			for(int j = 0; j<h; j++) {
				input[i*h+j]=(double)(int)board[i][j];
			}
		}
		n.feed_forward(input);
		delete[] input;
		n.back_propagate();
		printf("%c\n",bestmove);
		fflush(stdout);
		char oppm[5];
		scanf("%s",oppm);
		if(!strcmp(oppm,"O") || !strcmp(oppm,"X") || !strcmp(oppm,"T")) {
			if(!strcmp(oppm,"O")) {
				n.apply_changes(true);
			} else {
				n.apply_changes(false);
			}
			n.write_to_file(working_name);
			FILE * flog = fopen("netai.log","a");
			fprintf(flog,"%s\n",oppm);
			return 0;
		}
		if(!strcmp(oppm,"N")) {
			y2++;
		} else if(!strcmp(oppm,"E")) {
			x2++;
		} else if(!strcmp(oppm,"W")) {
			x2--;
		} else {
			y2--;
		}
		board[x2][y2]=1;
	}
	return 0;
}
