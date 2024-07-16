#include "validator.h"


void run() {
	int n = Int(1, Arg("maxn", int(1e5)));
	Endl();
	int x = Int(1, 30);
	Endl();
	int y = Int(1, 1000);
	Endl();
	vector<int> nums = SpacedInts(n, 1, 20);
	int ten = Arg("l10",0);
	if (ten) for (int i = 0; i < n; i++) assert(nums[i]==10);
	int ten20 = Arg("l1020",0);
	if (ten20) for (int i = 0; i < n; i++) assert(nums[i]==10||nums[i]==20);
	Eof();
}
