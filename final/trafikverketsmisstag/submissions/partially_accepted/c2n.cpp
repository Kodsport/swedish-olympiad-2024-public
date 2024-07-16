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
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#else
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debif(expr) if(expr) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())

bool path(int u, int p, int t, vvi& edges, vi& blocked)
{
	if (blocked[u] && (u != p)) return 0;
	if (u == t) return 1;
	repe(e, edges[u]) if (e != p) if (path(e, u, t, edges, blocked)) return 1;
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


	vector<squirrel> squirrels;
	rep(i, s)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		squirrels.emplace_back(squirrel({ a, b, i }));
	}
	vi blocked(n);
	repe(s, squirrels) blocked[s.start] = 1;

	vi order;
	while (squirrels.size())
	{
		bool any = 0;
		vector<squirrel> newsquirrels;
		repe(s, squirrels)
		{
			if (path(s.start, s.start, s.goal, edges, blocked))
			{
				order.push_back(s.index);
				blocked[s.start] = 0;
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