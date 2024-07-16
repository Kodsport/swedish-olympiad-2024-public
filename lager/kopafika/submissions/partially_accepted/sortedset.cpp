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

	int n, c;
	cin >> n >> c;
	vector<p2> items(n);
	rep(i, n) cin >> items[i].first;
	rep(i, n) cin >> items[i].second;

	vi ans(n);

	set<query> queries;

	rep(i, n)
	{
		query qu = { 0,c,i };
		queries.insert(qu);

		vector<query> topush;
		int cap = items[i].second;
		while (queries.size() && prev(end(queries))->weight >= cap)
		{
			query b = *prev(end(queries));
			queries.erase(prev(end(queries)));
			b.weight -= cap;
			b.value += items[i].first;
			topush.push_back(b);
		}
		repe(p, topush) queries.insert(p);
	}


	repe(qu, queries)
	{
		ans[qu.index] = qu.value;
	}
	

	rep(i, n)
	{
		cout << ans[i] << " ";
	}
	cout << "\n";

	return 0;
}