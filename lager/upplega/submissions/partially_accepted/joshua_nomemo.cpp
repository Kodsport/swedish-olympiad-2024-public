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

int best(int i, int k, int tooklast, vvi& profitleft, vvi& profitright)
{
	if (i == profitleft[0].size()) return 0;


	int ret = best(i+1,k,0,profitleft,profitright);
	if (k)
	{
		int delta;
		if (tooklast) delta = profitright[1][i]+profitleft[3][i] - profitright[1][i - 1];
		else delta = profitright[1][i] + profitleft[2][i];
		assert(delta>=0);
		ret = max(ret, delta + best(i + 1, k - 1, 1, profitleft, profitright));
	}
	return ret;
}

signed main()
{
	fast();

	int n, k;
	cin >> n >> k;

	vi positions(n);
	rep(i, n) cin >> positions[i];
	positions.insert(positions.begin(), -1); // Add dummy tree 0
	positions.push_back(inf);

	vi degrees(n);
	rep(i, n) cin >> degrees[i];
	degrees.insert(degrees.begin(), 0);
	degrees.push_back(0);
	
	n+=2;
	vector<vector<p2>> left(n);
	vector<vector<p2>> right(n);

	repp(i, 1, n-1)
	{
		vi h(degrees[i]);
		rep(j, degrees[i])cin >> h[j];
		rep(j, degrees[i])
		{
			int len;
			cin >> len;
			if (len > 0) right[i].emplace_back(h[j], len);
			else left[i].emplace_back(h[j], -len);
		}
	}
	
	vvi profitleft(4, vi(n));
	vvi profitright(4, vi(n));

	typedef array<int, 3> p3;
	auto getprofit = [&](int i, bool lefton, bool righton)
	{
		vi on(2);
		on[0] = lefton;
		on[1] = righton;

		vector<p3> events;
		repe(b, right[i])
		{
			events.push_back({b.first, b.second, true});
		}
		repe(b, left[i+1])
		{
			events.push_back({ b.first, b.second, false });
		}
		int saved = 0;
		sort(all(events));
		int longestleft = 0;
		int longestright = 0;

		int rightpos = positions[i + 1];
		int leftpos = positions[i];
		repe(ev, events)
		{
			int h=ev[0], w=ev[1], left=ev[2];
			int snowamount = 0;

			if (left)
			{
				int diff = (leftpos + w) - (rightpos - longestright) + 1;
				if (diff >= 0) snowamount = diff;
			}
			else
			{
				int diff = (leftpos + longestleft) - (rightpos - w) + 1;
				if (diff >= 0) snowamount = diff;
			}

			if (left && lefton || !left && righton) snowamount = w;
			saved += snowamount;
			if (left && lefton) longestleft = max(longestleft, w);
			else if (!left && righton) longestright = max(longestright, w);
		}

		return saved;
	};

	rep(i, n-1)
	{
		rep(a, 2)
		{
			rep(b,2)
			{
				if (a == 0 && b == 0) continue;
				int p = getprofit(i, a, b);
				//if(i==2&&a==1&&b==0) deb;
				//if (p) deb;
				if (a) profitright[a + 2 * b][i] += p;
				if (b) profitleft[a + 2 * b][i+1] += p;
			}
		}
	}

	cout << best(1, k, 0, profitleft, profitright);

	return 0;
}