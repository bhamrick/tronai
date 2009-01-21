#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<unistd.h>

using namespace std;

int main() {
	printf("RANDOM\n");
	fflush(stdout);
	srand(time(NULL)*getpid());
	char opp[21];
	scanf("%s",opp);
	int w, h, x1, x2, y1, y2;
	bool** board;
	scanf("%d%d",&w,&h);
	fprintf(stderr,"%d %d\n",w,h);
	board = new bool*[w];
	for(int i = 0; i<w; i++) {
		board[i] = new bool[h];
		for(int j = 0; j<h; j++) board[i][j] = 0;
	}
	scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	board[x1][y1] = board[x2][y2] = 1;
	while(1) {
		bool done = false;
		for(int i = 0; i<100 && !done; i++) {
			int rd = rand()%4;
			if(rd == 0) {
				if(y1 < h-1 && !board[x1][y1+1]) {
					printf("N\n");
					y1++;
					board[x1][y1]=1;
					done = true;
				}
			} else if(rd == 1) {
				if(x1 < w-1 && !board[x1+1][y1]) {
					printf("E\n");
					x1++;
					board[x1][y1]=1;
					done = true;
				}
			} else if(rd == 2) {
				if(x1 > 0 && !board[x1-1][y1]) {
					printf("W\n");
					x1--;
					board[x1][y1]=1;
					done = true;
				}
			} else if(rd == 3) {
				if(y1 > 0 && !board[x1][y1-1]) {
					printf("S\n");
					y1--;
					board[x1][y1]=1;
					done = true;
				}
			}
		}
		if(!done) printf("N\n");
		fflush(stdout);
		char oppm[5];
		scanf("%s",oppm);
		if(!strcmp(oppm,"O") || !strcmp(oppm,"X") || !strcmp(oppm,"T")) return 0;
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
