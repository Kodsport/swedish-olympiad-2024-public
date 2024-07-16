#include <bits/stdc++.h>
#include "validator.h"



using namespace std;

void run() {
	long long X = Int(1, 1e12);
	Space();
	int N = Int(1, Arg("maxN", int(2e5)));
	Space();
	int M = Int(1, Arg("maxM", int(2e5)));
	Space();
	int W = Int(1, 1e6);
	Space();
	long long T = Int(1, X);
	Endl();
	
	for (int i = 0; i < N; i++)
	{
		long long s = Int(1, X-1);
		Endl();
	}

	std::set <long long> seenD;
	for (int i = 0; i < M; i++){
		long long d = Int(1,T-1);
		Space();
		long long c = Int(1,1e9);
		Endl();

		if (seenD.find(d) != seenD.end()){
			die("Duplicate D value.");
		}

		seenD.insert(d);

	}
	
	Eof();
}
