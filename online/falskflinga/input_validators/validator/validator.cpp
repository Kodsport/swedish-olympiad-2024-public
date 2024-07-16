#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int N = Int(1,15); Endl();
	int n_is = Arg("n",-1);
	if (n_is!=-1) assert(N==n_is);

	for (int i = 0; i < N; i++) {
		string s = Line();
		assert(s.size() == N);
		for (int j = 0; j < N; j++) {
			assert(s[j] == '0' || s[j] == '1');
		}
	}

	Eof();
}
