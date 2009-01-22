#include<cstdio>
#include<cstdlib>

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("Usage: %s logfile bsename\n",argv[0]);
		return 0;
	}
	char results[2], *dataname, *plotname;
	asprintf(&dataname,"%s.data",argv[2]);
	asprintf(&plotname,"%s.plot",argv[2]);
	FILE * fin = fopen(argv[1],"r"), *fdata = fopen(dataname,"w"), *fplot = fopen(plotname,"w");
	int r = fscanf(fin,"%s",results);
	double wrate=0;
	int games=0;
	double wins = 0;
	for(int i = 0; i<100; i++) {
		games++;
		if(results[0]=='O') wins+=1.0;
		else if(results[0]=='T') wins+=0.5;
		fscanf(fin,"%s",results);
	}
	wrate = wins/games;
	printf("%lf %d %lf\n",wins,games,wrate);
	while(r!=EOF) {
		games++;
		wrate *= 0.99;
		if(results[0] == 'O') {
			wrate += 0.01;
		} else if(results[0] == 'T') {
			wrate += 0.005;
		}
		fprintf(fdata,"%d %lf\n",games,wrate);
		r = fscanf(fin,"%s",results);
	}
	fclose(fdata);
	fprintf(fplot,"plot [%d:%d] [0:1] '%s' smooth unique\n",11,games,dataname);
	fclose(fplot);
	fclose(fin);
	return 0;
}
