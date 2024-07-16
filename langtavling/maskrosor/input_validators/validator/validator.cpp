#include <bits/stdc++.h>
#include "validator.h"



using namespace std;

void run() {
	int r = Int(1, Arg("maxR", int(1e9)));
	Space();
	int c = Int(1, Arg("maxC", int(1e9)));
	Endl();
	int n = Int(1, Arg("maxN", int(300)));
	Endl();
	
	set<pair<int,int>> seen;
	for (int i = 0; i < n; i++)
	{
		int a = Int(1, r);
		Space();
		int b = Int(1, c);
		Endl();
		pair<int,int> p = {a,b};
		assert(seen.find(p)==seen.end());
		seen.insert(p);
	}

	
	Eof();
}
