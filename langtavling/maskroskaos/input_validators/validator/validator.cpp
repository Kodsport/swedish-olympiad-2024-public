#include <bits/stdc++.h>
#include "validator.h"



#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <random>
#include <chrono>
#include <cassert>
#include <numeric>
#include <bitset>



using namespace std;

void run() {
	int n = Int(1, Arg("maxN"));
	Endl();
	
	vector<int> seen(n*2);
	for (int i = 0; i < n; i++)
	{
		int a = Int(1, n*2);
		Space();
		int b = Int(1, n*2);
		Endl();
		a--;b--;
		assert(!seen[a]);
		seen[a]=1;
		assert(!seen[b]);
		seen[b]=1;
	}
	
	Eof();
}
