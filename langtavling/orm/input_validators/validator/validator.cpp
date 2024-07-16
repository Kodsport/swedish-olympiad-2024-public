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
	int n = Int(1, Arg("maxN", int(1000)));
	Endl();
	
	vector<int> seen(n*3);
	for (int i = 0; i < 3; i++)
	{
		vector<int> row = SpacedInts(n, 0, n*3);
		for (int j = 0; j < n; j++) 
		{
			if (row[j]==0) continue;
			assert(!seen[row[j]-1]);
			seen[row[j]-1]=1;
		}
	}
	
	Eof();
}
