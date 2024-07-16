#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int maxSegment = Arg("maxSegSize", int(1e9));

	int l = Int(1, maxSegment);
	Space();
	int r = Int(1, maxSegment);
	assert(r>l);
	Endl();
	
	int q = Int(1, Arg("maxq", int(2e5)));
	Endl();
	
	vector<int> cnt(int(1e6));
	vector<int> active(int(1e6));
	int numactive = 0;
	for (int i = 0; i < q; i++)
	{
		char t = Char();
		Space();
		int id = Int(1, int(1e6));

		if (t=='+')
		{
			assert(cnt[id]==0);
			assert(active[id]==0);
			active[id]=1;
			cnt[id]++;
			Space();
			int lo = Int(1,maxSegment);
			Space();
			int hi = Int(1,maxSegment);
			assert(hi>lo);
		}
		else
		{
			assert(active[id]==1);
			active[id]=0;
		}
		Endl();
	}


	Eof();
}
