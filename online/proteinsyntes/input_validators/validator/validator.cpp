#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int n = Int(1, Arg("maxn", int(1e5))); Endl();
	string s = Line();
	assert(s.size()==n);
	int m = Int(1, Arg("maxm", int(1e6))); Endl();

	int totlen = 0;
	for (int i = 0; i < m; i++)
	{
		string k = Line();
		totlen += k.size();
		for (int j = 0; j < k.size(); j++) assert(k[j]>='a'&&k[j]<='z');
	}
	assert(totlen<=1e6);

	Eof();
}
