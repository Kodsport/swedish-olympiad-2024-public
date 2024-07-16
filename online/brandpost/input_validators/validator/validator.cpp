#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int maxSize = Arg("maxSize", 1000);
	int w = Int(1, maxSize); Space();
	int h = Int(1, maxSize); Space();
	int n = Int(1, Arg("maxN", 20000)); Endl();

	assert(!(w==1 && h==1));

	int used[w+1][h+1];

	for (int i = 0; i < w+1; i++){
		for (int j = 0; j < h+1; j++){
			used[i][j]=0;
		}
	}

	for (int i = 0; i < n; i++){
		int x,y;
		x = Int(1, w); Space();
		y = Int(1, h); Endl();

		if (used[x][y]==1){
			die("Duplicate coordinates of brandpost used! Used:" + to_string(x) + " " + to_string(y));
		}
		used[x][y]=1;
	}

	string mode = Arg("mode","");

	if (mode == "hydrantAtStart"){
		assert(n==1);
		assert(used[1][1]==1);
	}
	

	Eof();
}
