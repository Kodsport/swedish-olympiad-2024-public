#include "validator.h"


using namespace std;


void run() {
	string s = Line();
	assert(s.size() <= 50);
	for (int i = 0; i < s.size(); i++) assert(s[i]>='a'&&s[i]<='z');

	int k = Int(1, Arg("max_k", s.size())); Endl();
	int ab = Arg("ab",0);
	if (ab)
	{
		for (int i = 0; i < s.size(); i++) assert(s[i]=='a'||s[i]=='b');
	}

	Eof();
}
