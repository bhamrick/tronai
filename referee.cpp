#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<curses.h>
#include<unistd.h>

void readline(int p, char* ans, int n) {
	int i = -1;
	do {
		i++;
		read(p,ans+i,1);
		if(*(ans+i)==10) {
			*(ans+i) = 0;
			return;
		}
	} while(i < n-1);
}

int main(int argc, char** argv) {
	if(argc < 5) {
		fprintf(stderr,"Usage: %s width height player1 player2\n",argv[0]);
		return(0);
	}
	int w, h;
	sscanf(argv[1],"%d",&w);
	sscanf(argv[2],"%d",&h);
	
	int oldstdin = dup(0), oldstdout = dup(1);
	int stdin1[2], stdin2[2], stdout1[2], stdout2[2];
	pipe(stdin1);
	pipe(stdin2);
	pipe(stdout1);
	pipe(stdout2);

	if(!fork()) {
		//player 1
		dup2(stdin1[0],0);
		dup2(stdout1[1],1);
		close(stdin1[1]);
		close(stdout1[0]);
		close(stdin2[0]);
		close(stdin2[1]);
		close(stdout2[0]);
		close(stdout2[1]);
		char* cargv[2] = {argv[3],NULL};
		execv(cargv[0],cargv);
	} else if(!fork()) {
		//player 2
		dup2(stdin2[0],0);
		dup2(stdout2[1],1);
		close(stdin1[0]);
		close(stdin1[1]);
		close(stdout1[0]);
		close(stdout1[1]);
		close(stdin2[1]);
		close(stdout2[0]);
		char* cargv[2] = {argv[4],NULL};
		execv(cargv[0],cargv);
	} else {
		//referee
		close(stdin1[0]);
		close(stdout1[1]);
		close(stdin2[0]);
		close(stdout2[1]);
		char name1[21], name2[21];
		for(int i = 0; i<21; i++) name1[i]=name2[i]=0;
		readline(stdout1[0],name1,20);
		readline(stdout2[0],name2,20);
		printf("%s vs %s\n",name1,name2);
		printf("aBLARGH\n");
		write(stdin1[1],name2,strlen(name2));
		write(stdin2[1],name1,strlen(name1));
		write(stdin1[1],"\n",1);
		write(stdin2[1],"\n",1);
		char** dims = new char*;
		asprintf(dims,"%d %d\n",w,h);
		printf("aBLARGH %s\n",*dims);
		write(stdin1[1],*dims,strlen(*dims));
		write(stdin2[1],*dims,strlen(*dims));
		free(*dims);
		char** loc1 = new char*, **loc2 = new char*;
		bool** board;
		printf("aBLARGH\n");
		int x1=w/4, y1=h/2, x2=3*w/4, y2=h/2;
		asprintf(loc1,"%d %d %d %d\n",w/4,h/2,3*w/4,h/2);
		asprintf(loc2,"%d %d %d %d\n",3*w/4,h/2,w/4,h/2);
		write(stdin1[1],*loc1,strlen(*loc1));
		write(stdin2[1],*loc2,strlen(*loc2));
		free(*loc1);
		free(*loc2);
		printf("aBLARGH");

		board = new bool*[w];
		for(int i = 0; i<w; i++) {
			board[i] = new bool[h];	
			for(int j = 0; j<h; j++)
				board[i][j] = 0;
		}
		board[x1][y1]=board[x2][y2]=1;
		char mov1[5], mov2[5];
		while(true) {
			readline(stdout1[0],mov1,4);
			readline(stdout2[0],mov2,4);
			if(!strcmp(mov1,"N")) {
				y1++;
			} else if(!strcmp(mov1,"E")) {
				x1++;
			} else if(!strcmp(mov1,"W")) {
				x1--;
			} else {
				y1--;
			}
			if(!strcmp(mov2,"N")) {
				y2++;
			} else if(!strcmp(mov2,"E")) {
				x2++;
			} else if(!strcmp(mov2,"W")) {
				x2--;
			} else {
				y2--;
			}
			printf("%s %s\n",mov1,mov2);
			if(((x1 < 0 || x1 >= w || y1 < 0 || y1 >= h) && (x2 < 0 || x2 >=w || y2 < 0 || y2 >=h)) || (x1 >= 0 && x1 < w && y1 >= 0 && y1 < h && x2 >= 0 && x2 < w && y2 >= 0 && y2 < h && board[x1][y1] && board[x2][x2])) {
				write(stdin1[1],"T",2);
				write(stdin2[1],"T",2);
				write(stdin1[1],"\n",1);
				write(stdin2[1],"\n",1);
				break;
			} else if(x1 < 0 || x1 >= w || y1 < 0 || y1 >=h || board[x1][y1]) {
				write(stdin1[1],"X",2);
				write(stdin2[1],"O",2);
				write(stdin1[1],"\n",1);
				write(stdin2[1],"\n",1);
				break;
			} else if(x2 < 0 || x2 >= w || y2 < 0 || y2 >=h || board[x2][y2]) {
				write(stdin1[1],"O",2);
				write(stdin2[1],"X",2);
				write(stdin1[1],"\n",1);
				write(stdin2[1],"\n",1);
				break;
			}
			board[x1][y1]=board[x2][y2]=1;
			printf("\n");
			for(int r = h-1; r>=0; r--) {
				for(int c = 0; c<w; c++) {
					if(board[c][r]) printf("#");
					else printf("_");
				}
				printf("\n");
			}
			write(stdin1[1],mov2,4);
			write(stdin2[1],mov1,4);
			write(stdin1[1],"\n",1);
			write(stdin2[1],"\n",1);
		}
	}
}
