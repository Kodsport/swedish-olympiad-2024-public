#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int r = Int(1, Arg("maxr", 500)); Endl();
	int c = Int(1, Arg("maxc", 500)); Endl();
	int q = Int(0, Arg("maxq", int(1e5))); Endl();
	vector<string> rows;
	int numStockholm = 0;
	for (int i = 0; i < r; i++)
	{
		rows.push_back(Line());
		assert(rows.back().size()==c);
		for (int j = 0; j < c; j++) numStockholm += rows[i][j]=='S';
	}
	assert(numStockholm==1);
	for (int i = 0; i < q; i++)
	{
		int a = Int(1, r);
		Space();
		int b = Int(1, c);
		Endl();
		a--; b--;
		assert(rows[a][b]=='.');
		rows[a][b]='#';
	}
	Eof();
}
