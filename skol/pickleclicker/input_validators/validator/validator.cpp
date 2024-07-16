#include "validator.h"


using namespace std;


void run() {
	int n = Int(1, Arg("n",6));
	Space();
	int t = Int(1, Arg("max_t", int(1e5)));
	Endl();

	for (int i = 0; i < n; i++)
	{
		int p = Int(1, t);
		Space();
		int c = Int(1, t);
		Endl();
	}
	
	Eof();
}
