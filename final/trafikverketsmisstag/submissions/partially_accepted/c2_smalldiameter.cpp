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


struct squirrel
{
	int start, goal, index;
};

vi par;
vi depth;
vi active;
vector<squirrel> squirrels;
void dfs2(int u, int p, int d, vvi& edges)
{
	par[u] = p;
	depth[u] = d;
	repe(e, edges[u]) if (e != p) dfs2(e, u, d + 1, edges);
}

int pathsum(int a, int b)
{
	int ret = active[a]+active[b];
	if (depth[a] < depth[b]) swap(a, b);
	while (depth[a] > depth[b]) a = par[a], ret += active[a];
	while (a!=b)
	{
		a = par[a];
		b = par[b];
		ret += active[a] + active[b];
	}
	return ret-active[b];
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

	squirrels.resize(n);
	vector<squirrel> squirrellist;
	active.resize(n);
	rep(i, s)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		active[a] = 1;
		squirrels[a] = squirrel({ a, b, i });
		squirrellist.emplace_back(squirrel({ a, b, i }));
	}

	par.resize(n);
	depth.resize(n);
	dfs2(0, 0, 0, edges);

	vi order;

	while (squirrellist.size())
	{
		bool any = 0;

		vector<squirrel> newsquirrels;
		repe(s, squirrellist)
		{
			if (pathsum(s.start, s.goal) == 1)
			{
				order.push_back(s.index);
				active[s.start] = 0;
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