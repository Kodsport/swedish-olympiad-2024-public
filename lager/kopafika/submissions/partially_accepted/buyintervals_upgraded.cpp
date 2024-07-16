#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;
typedef tuple<int, int, int> p3;

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
ll elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]

struct Node;
struct ptr {
	int index = 0;
	Node* operator->();
	explicit operator bool();
};

struct Node
{
	ptr l, r;
	ll sum = 0;

	void init(int x) { sum = x; }
	void init(ptr l, ptr r) {
		this->l = l;
		this->r = r;
		if (l) sum += l->sum;
		if (r) sum += r->sum;
	}
};
const int NODE_TEMPS = 10'000'000;
Node nodeTemps[NODE_TEMPS];
int tempInd = 2;
ptr::operator bool() {
	return index != 0;
}
Node* ptr::operator->() {
	assert(index != 0);
	return &nodeTemps[index];
}
ptr emptyNode{1};

template<class... Params>
ptr newNode(Params... params) {
	assert(tempInd < NODE_TEMPS);
	ptr ret{tempInd++};
	ret->init(params...);
	return ret;
}

ptr roots[int(2e5 + 10)];
ptr rootsprofit[int(2e5 + 10)];

ptr build(int l, int r)
{
	if (l == r) return emptyNode;
	int mid = (l + r) >> 1;
	return newNode(build(l, mid), build(mid + 1, r));
}

ptr update(ptr x, int l, int r, int i, int v)
{
	if (l == r) return newNode(v);
	int mid = (l + r) >> 1;
	if (i <= mid) return newNode(update(x->l, l, mid, i, v), x->r);
	else return newNode(x->l, update(x->r, mid + 1, r, i, v));
}

ll query(ptr x, int l, int r, int ql, int qr)
{
	if (l > qr || r < ql) return 0;
	if (l >= ql && r <= qr) return x->sum;
	int mid = (l + r) >> 1;
	return query(x->l, l, mid, ql, qr) + query(x->r, mid + 1, r, ql, qr);
}

bool binsearch(ptr x, int l, int r, int ql, ll& rem, int& out)
{
	if (r < ql) return true;
	if (ql <= l) {
		if (x->sum <= rem) {
			rem -= x->sum;
			return true;
		}
	}

	if (l == r) {
		out = l;
		return false;
	}

	int mid = (l + r) / 2;
	return
		binsearch(x->l, l, mid, ql, rem, out) &&
		binsearch(x->r, mid+1, r, ql, rem, out);
}

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

	vector<p3> itemssorted;
	rep(i, n)
	{
		itemssorted.emplace_back(items[i].second, items[i].first, i);
	}
	sort(all(itemssorted));

	roots[0] = build(0, n - 1);
	rootsprofit[0] = build(0, n - 1);
	vi weightssorted;

	repe(item, itemssorted)
	{
		int w, p, i;
		tie(w, p, i) = item;
		weightssorted.emplace_back(w);
		roots[sz(weightssorted)] = update(roots[sz(weightssorted) - 1], 0, n - 1, i, w);
		rootsprofit[sz(weightssorted)] = update(rootsprofit[sz(weightssorted) - 1], 0, n - 1, i, p);
	}

	rep(q, n)
	{
		ll cap = c;
		ll profit = 0;
	
		int i = q;
		while (i<n)
		{
			auto it = upper_bound(all(weightssorted), cap);
			if (it == begin(weightssorted)) break;
			it = prev(it);
			int ind = (int)(it - begin(weightssorted)+1);
			ptr root = roots[ind];

			// find max lo s.t. query(i, lo) <= cap
			ll rem = cap;
			int hi = n;
			binsearch(root, 0, n - 1, i, rem, hi);
			int lo = hi - 1;

			if (lo>=i)
			{
				profit += query(rootsprofit[ind], 0, n - 1, i, lo);
				cap -= query(root, 0, n - 1, i, lo);
				i = lo + 1;
			}
			i++;
		}
		
		cout << profit << " ";
	}

	cout << endl;
	_Exit(0);
}
