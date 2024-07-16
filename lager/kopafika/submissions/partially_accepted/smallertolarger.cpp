#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>
using namespace __gnu_pbds;
template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

#define _LOCAL _MSC_VER
#if _LOCAL > 0
#define deb __debugbreak();
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
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]

struct query {
	int value;
	int weight;
	int index;

	bool operator<(const query& other) const {
		if (weight != other.weight) return weight < other.weight;
		return index < other.index;
	}

};


signed main()
{
	fast();

#if 0 && _LOCAL
	ifstream in("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
	cin.rdbuf(in.rdbuf());
#endif

	int n, c;
	cin >> n >> c;
	vector<p2> items(n);
	rep(i, n) cin >> items[i].first;
	rep(i, n) cin >> items[i].second;

	set<p2> res;
	int lazyprofit = 0;
	int lazyweight = 0;

	indexed_set<query> queries;

	// items are:
	// value+lazyprofit
	// weight-lazyweight
	rep(i, n)
	{
		query qu = { -lazyprofit, c+lazyweight, i };
		queries.insert(qu);
		int split = queries.order_of_key(query({ -1, items[i].second + 1+lazyweight, -1 }));
		vector<query> readd; // in normal form
		if (split<queries.size()/2) // many must buy
		{
			while (queries.size()&&queries.begin()->weight-lazyweight<items[i].second)
			{
				query qu = *queries.begin();
				queries.erase(queries.begin());
				qu.value += lazyprofit;
				qu.weight -= lazyweight;
				readd.push_back(qu);
			}
			lazyprofit += items[i].first;
			lazyweight += items[i].second;
		}
		else
		{
			while (queries.size() && prev(queries.end())->weight - lazyweight >= items[i].second)
			{
				query qu = *prev(queries.end());
				queries.erase(prev(queries.end()));
				qu.value += lazyprofit;
				qu.weight -= lazyweight;
				qu.value += items[i].first;
				qu.weight -= items[i].second;
				readd.push_back(qu);
			}
		}
		repe(v, readd)
		{
			v.value -= lazyprofit;
			v.weight += lazyweight;
			queries.insert(v);
		}
	}

	vi ans(n);

	repe(qu, queries)
	{
		ans[qu.index] = qu.value+lazyprofit;
	}


	rep(i, n)
	{
		cout << ans[i] << " ";
	}
	cout << "\n";

	return 0;
}