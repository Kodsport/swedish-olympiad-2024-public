// sort squirrels by distance to node in middle of diameter
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

bool path(int u, int p, int t, vvi& edges, vi& blocked)
{
	if (blocked[u] && (u != p)) return 0;
	if (u == t) return 1;
	repe(e, edges[u]) if (e != p) if (path(e, u, t, edges, blocked)) return 1;
	return 0;
}

const int maxn = int(2e5);
int tin[maxn];
int tout[maxn];
int timer = 0;
void dfs(int u, int p, vvi& edges)
{
	tin[u] = timer++;
	repe(e, edges[u]) if (e != p) dfs(e, u, edges);
	tout[u] = timer++;
}

p2 furthest = p2(-1,-1);
void dfs2(int u, int p, int d, vvi& edges)
{
	if (d > furthest.second) furthest = p2(u, d);
	
	repe(e, edges[u]) if (e != p) dfs2(e, u, d + 1, edges);
}
int depth[maxn];
void dfs3(int u, int p, int d, vvi& edges)
{
	depth[u] = d;
	repe(e, edges[u]) if (e != p) dfs3(e, u, d + 1, edges);
}

bool dfs4(int u, int p, int t, vvi& edges, vi& path)
{
	path.push_back(u);
	if (u == t) return 1;
	repe(e, edges[u]) if (e != p) if (dfs4(e,u,t,edges,path)) return 1;
	path.pop_back();
	return 0;
}

struct squirrel
{
	int start, goal, index;
};

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
	LCA lc(edges);
	Tree tree(n*2);
	dfs(0, 0, edges);
	dfs2(0, 0, 0, edges);
	int k = furthest.first;
	dfs2(k, k, 0, edges);
	vi path;
	int v = furthest.first;
	dfs3(v, v, 0, edges);
	dfs4(v, v, k, edges, path);
	int midoid = path[path.size() / 2];
	dfs3(midoid, midoid, 0, edges);

	vector<squirrel> squirrels;
	rep(i, s)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree.update(tin[a], 1);
		tree.update(tout[a], -1);
		squirrels.emplace_back(squirrel({ a, b, i }));
	}
	sort(all(squirrels), [](const squirrel& l, const squirrel& r)
		{
			return depth[l.start] < depth[r.start];
		});

	auto pathfast = [&](int a, int b)
	{
		int lca = lc.lca(a, b);
		int nums = tree.query(tin[a]) + tree.query(tin[b]) - 2 * tree.query(tin[lca]) + tree.sum(tin[lca],tin[lca]);
		assert(nums >= 1);
		return nums == 1;
	};

	vi order;
	auto print = [&]()
	{
		rep(i, tree.tree.size() - 1) cout << tree.sum(i, i) << " ";
		cout << "\n";
	};
	//print();
	while (squirrels.size())
	{
		bool any = 0;
		
		vector<squirrel> newsquirrels;
		repe(s, squirrels)
		{
			if (pathfast(s.start, s.goal))
			{
				order.push_back(s.index);
				tree.update(tin[s.start], -1);
				//print();
				tree.update(tout[s.start], 1);
				//print();
				any = 1;
			}
			else newsquirrels.push_back(s);
		}
		squirrels = newsquirrels;
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