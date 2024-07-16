#include "validator.h"


using namespace std;


void run() {
	string s = Line();
	assert(s.size()<=10);

	for (int i=0; i<=s.size(); i++){
		assert('a'<=s[i]<='z');
	}

	int k = Int(1, Arg("maxk", 9)); Endl();

	Eof();
}
