#include <bits/stdc++.h>
#include "validator.h"


using namespace std;

int MAXN = int(2e5);
int MAXC = int(1e9);
void run() {
	int n = Int(1, Arg("maxn", MAXN));
	Space();
	int c = Int(1, Arg("maxc", MAXC));
	Endl();

	vector<int> profits = SpacedInts(n, 1, int(1e9));
	vector<int> costs = SpacedInts(n, 1, int(1e9));

	int increasing = Arg("increasing", 0);
	if (increasing)
	{
		for (int i = 0; i < n-1; i++) assert(costs[i]<=costs[i+1]);
	}

	Eof();
}
