#include "validator.h"

void run() {
	int maxn = Arg("maxn", int(1e5));
	string mode = Arg("mode","");
	int setk = Arg("k", 0);

	int n = Int(2, maxn);
	Space();
	int k = Int(1, n-1);
	if (setk) assert(k == setk);
	Endl();
	
	
	int parents[n-1];

	for (int i = 0; i<n-1; i++){
		parents[i] = Int(1,i+1);
		assert(parents[i] <= i + 1);
		if (i != n-2) Space();

		if (mode == "line") assert(parents[i] == i+1);
		
	}
	Endl();



	Eof();
}
