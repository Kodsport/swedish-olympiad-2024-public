#include "validator.h"

void run() {
	int n = Int(1, int(1e6));
	Space();
	int m = Int(1, int(1e6));
	Space();
	int retstart = Int(0,1);
	Endl();
	assert(n*m<=int(1e6));
	assert(n*m>=2);
	int ret = Arg("r",-1);
	if (ret!=-1) assert(retstart==ret);

	int xcnt = 0;
	vector<string> rows;
	int r = -1;
	int c = -1;
	vector<int> good(250);
	good['X']=1;
	good['S']=1;
	good['.']=1;
	int ocnt = 0;
	for (int i = 0; i < n; i++)
	{
		string row = Line();
		rows.push_back(row);
		assert(row.size()==m);
		for (int j = 0; j < m; j++) assert(good[row[j]]);

		for (int j = 0; j < m; j++) xcnt += row[j]=='X';
		for (int j = 0; j < m; j++) if (row[j]=='S') xcnt++, ocnt++, r=i,c=j;

	}
	assert(ocnt==1);
	assert(rows[r][c]=='S');
	assert(xcnt<=int(Arg("maxX", int(2e4))));
	assert(xcnt>=2);
	Eof();
}
