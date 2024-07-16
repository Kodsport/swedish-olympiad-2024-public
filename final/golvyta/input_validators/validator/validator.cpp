#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int maxn = Arg("maxn", int(300000));
	int downright = Arg("downright", int(0));

	int n = Int(1, maxn);
	Endl();
	string s = Line();
	assert(s.length() == n);
	//Endl();
	int r = Int(0, 300000-1);
	Space();
	int c = Int(0, 300000-1);
	Endl();
	
	for(int c1 = 0; c1 < n; c1++){
		assert(s[c1] == 'v' || s[c1] == '^' || s[c1] == '<' || s[c1] == '>');
		if(downright == 1){
			assert(s[c1] == '>' || s[c1] == 'v');
		}
	}

	Eof();
}
