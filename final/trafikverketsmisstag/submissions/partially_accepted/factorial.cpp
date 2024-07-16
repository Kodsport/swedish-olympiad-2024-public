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
	if (blocked[u]) return 0;
	if (u == t) return 1;
	repe(e, edges[u]) if (e != p) if (path(e, u, t, edges, blocked)) return 1;
	return 0;
}

signed main()
{
	fast();

	int n, s;
	cin >> n >> s;
	vvi edges(n);
	rep(i, n-1)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	typedef tuple<int,int,int> p3;
	vector<p3> squirrels;
	rep(i, s)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		squirrels.emplace_back(a, b, i);
	}
	sort(all(squirrels));
	do
	{
		vi blocked(n);
		repe(s, squirrels) blocked[get<0>(s)] = 1;
		bool works = 1;
		repe(s, squirrels)
		{
			int a, b, i;
			tie(a, b, i) = s;
			blocked[a] = 0;
			works &= path(a, a, b, edges, blocked);
		}
		if (works)
		{
			cout << "Yes\n";
			repe(s, squirrels)
			{
				cout << get<2>(s) + 1 << " ";
			}
			cout << "\n";
			return 0;
		}
	} while (next_permutation(all(squirrels)));


	cout << "No\n";

	return 0;
}