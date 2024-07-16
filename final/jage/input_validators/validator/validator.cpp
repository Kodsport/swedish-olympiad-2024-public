#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	int maxn = Arg("maxn", int(100000));
	int maxm = Arg("maxm", int(100000));

	int n = Int(2, maxn);
	Space();
	int m = Int(1, maxm);
	Endl();

	set<string> names;
	string line = Line();

	stringstream ss;
	ss << line;
	
	string name;
	int count = 0;
	while (ss >> name) {
		count++;
		assert(names.find(name) == names.end());
		names.insert(name);
	}
	assert(count == n);

	for (int i = 0; i < m; i++) {
		string action = Line();
		stringstream ss;
		ss << action;
		string name1, tmp, name2;
		ss >> name1 >> tmp >> name2;
		assert(name1 != name2);
		assert(names.find(name1) != names.end());
		assert(names.find(name2) != names.end());
	}

	Eof();
}
