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


signed main()
{
	fast();

	int n, c;
	cin >> n >> c;
	vector<p2> items(n);
	rep(i, n) cin >> items[i].first;
	rep(i, n) cin >> items[i].second;

	vi pref(n);
	pref[0] = items[0].second;
	repp(i, 1, n) pref[i] = items[i].second + pref[i - 1];
	
	vi pref2(n);
	pref2[0] = items[0].first;
	repp(i, 1, n) pref2[i] = items[i].first + pref2[i - 1];

	auto query = [](vi& pref, int l, int r) // [l,r]
	{
		if (l) l = pref[l - 1];
		return pref[r] - l;
	};

	rep(s, n)
	{
		int cap = c;
		int p = 0;

		int i = s;
		while (i<n)
		{
			int lo = i-1;
			int hi = n;
			while (lo+1<hi)
			{
				int mid = (lo + hi) / 2;
				if (query(pref, i, mid) <= cap) lo = mid;
				else hi = mid;
			}

			if (lo >= i)
			{
				p += query(pref2, i, lo);
				cap -= query(pref, i, lo);
				i = lo + 1;
			}
			break;
		}

		cout << p << " ";
	}
	cout << "\n";

	return 0;
}