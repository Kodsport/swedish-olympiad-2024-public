#include "validator.h"

struct UF {
	vector<int> v;
	UF(int n) : v(n, -1) {}
	int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (-v[a] < -v[b]) swap(a, b);
		v[a] += v[b];
		v[b] = a;
		return true;
	}
};

pair<int,int> furthest = {-1,-1};
void dfs(int u, int p, int d, vector<vector<int>>& edges)
{
	if (d>furthest.second) furthest = {u,d};
	for (auto& e : edges[u]) if (e!=p) dfs(e,u,d+1,edges);
}

void run() {
	int n = Int(1, Arg("maxn", int(2e5)));
	Space();
	int c = Int(1, Arg("maxc", int(2e5)));
	Endl();
	
	vector<vector<int>> edges(n);
	UF uf(n);
	for (int i = 0; i < n-1; i++)
	{
		int a = Int(1,n);
		Space();
		int b = Int(1,n);
		Endl();
		a--; b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
		assert(uf.join(a,b));
	}
	dfs(0,0,0,edges);
	dfs(furthest.first,furthest.first,0,edges);
	int diameter = Arg("diameter", n+1);
	assert(furthest.second<diameter);

	vector<int> used(n);
	for (int i = 0; i < c; i++)
	{
		int a = Int(1,n);
		Space();
		int b = Int(1,n);
		Endl();
		a--; b--;
		assert(!used[a]);
		used[a]=1;
	}
	
	Eof();
}
