#include <bits/stdc++.h>
#include "validator.h"


using namespace std;


void run() {
	string s = Line();
	assert(s.size()>=1);
	assert(s.size()<=200);
	set<char> chars;
	for (int i=0;i<s.size();i++) chars.insert(s[i]);
	assert(chars.size()<=int(Arg("max")));

	Eof();
}
