#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#if _MSC_VER > 0
#define deb __debugbreak;
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())


template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			repp(j, 0, sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

struct Tree
{
	vi tree;
	Tree(int n) : tree(n + 1) {}

	void update(int i, int v)
	{
		for (i++; i < tree.size(); i += i & -i)
			tree[i] += v;
	}

	int query(int r)
	{
		int ret = 0;
		for (r++; r > 0; r -= r & -r)
			ret += tree[r];
		return ret;
	}

	int sum(int l, int r)
	{
		if (l) l = query(l - 1);
		return query(r) - l;
	}
};

struct pathsum
{
	int n;
	LCA lc;
	vvi up;
	Tree fenwick;
	vi tin;
	vi tout;
	vi depth;
	pathsum(vvi& edges) : n(edges.size()), lc(edges), fenwick(n * 2), tin(n), tout(n), up(n, vi(19)), depth(n)
	{
		dfs(0, 0, 0, edges);
	}

	void update(int i, int v)
	{
		fenwick.update(tin[i], v);
		fenwick.update(tout[i], -v);
	}

	int timer = 0;
	void dfs(int u, int p, int d, vvi& edges)
	{
		depth[u] = d;
		up[u][0] = p;
		repp(d, 1, 19)
		{
			up[u][d] = up[up[u][d-1]][d-1];
		}

		tin[u] = timer++;
		repe(e, edges[u]) if (e != p) dfs(e, u, d+1, edges);
		tout[u] = timer++;
	}

	int query(int a, int b)
	{
		int lca = lc.lca(a, b);
		int nums = fenwick.query(tin[a]) + fenwick.query(tin[b]) - 2 * fenwick.query(tin[lca]) + fenwick.sum(tin[lca], tin[lca]);
		return nums;
	}
};



struct squirrel
{
	int start, goal, index;
};

vector<squirrel> squirrels;
void dfs2(int u)
{

}


signed main()
{
	fast();

	int n, s;
	cin >> n >> s;
	vvi edges(n);
	rep(i, n - 1)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	pathsum path(edges);
	squirrels.resize(n);
	vector<squirrel> squirrellist;
	rep(i, s)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		path.update(a, 1);
		squirrels[a] = squirrel({ a, b, i });
		squirrellist.emplace_back(squirrel({ a, b, i }));
	}

	vi order;

	while (squirrellist.size())
	{
		bool any = 0;

		vector<squirrel> newsquirrels;
		repe(s, squirrellist)
		{
			if (path.query(s.start, s.goal) == 1)
			{
				order.push_back(s.index);
				path.update(s.start, -1);
				any = 1;
			}
			else newsquirrels.push_back(s);
		}
		squirrellist = newsquirrels;
		if (!any) break;
	}

	if (order.size() == s)
	{
		cout << "Yes\n";
		repe(i, order) cout << i + 1 << " ";
		cout << "\n";
		return 0;
	}

	cout << "No\n";

	return 0;
}