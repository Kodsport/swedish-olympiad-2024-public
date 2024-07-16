#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int n = Int(0, Arg("n", int(1e5)));
	Space();
	int t = Int(1, Arg("t", int(1e9)));
	Space();
	int s = Int(1, t);
	Endl();
	
	int last = -1;
	for (int i = 0; i < n; i++)
	{
		int l = Int(last, t);
		Space();
		int r = Int(l+1,t);
		Endl();
		last = r;
	}

	Eof();
}
