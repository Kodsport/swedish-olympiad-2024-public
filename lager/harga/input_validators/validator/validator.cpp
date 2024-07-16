#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int maxn = Arg("maxn", int(300000));
	int identity = Arg("identity", int(0));
	int permutation = Arg("permutation", int(0));

	int n = Int(1, maxn);
	Space();
	int m = Int(1, maxn);
	Endl();

	vector<int> X = SpacedInts(n, 1, m);
	vector<int> F = SpacedInts(m, 1, m);

	if(permutation == 1){
		identity = 1;
		sort(F.begin(), F.end());
	}

	if(identity == 1){
		for(int c1 = 0; c1 < m; c1++){
			assert(F[c1] == c1+1);
		}
	}

	Eof();
}
