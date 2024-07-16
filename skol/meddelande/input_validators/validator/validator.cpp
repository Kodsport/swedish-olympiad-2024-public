#include "validator.h"


using namespace std;


void run() {
	int n = Int(1, Arg("maxn",6));
	Space();
	int m = Int(1, 6);
	
	int fill = Arg("fill",0);
	Endl();

	int c = 0;

	for(int i = 0; i < n; i++){
		string s = Line();
		assert(s.size() == m);
		for (int j = 0; j<m; j++){
			assert(s[j] == '.' || isalpha(s[j]));
			if (isalpha(s[j])){
				c++;
			}
		}
	}

	if (fill){
		if (c!=n+m-1){
			die("There are " + to_string(c) + " characters, but expected " + to_string(n) + " + " + to_string(m) + " - 1 (n+m-1) characters.");
		}
	}

	Eof();
}
