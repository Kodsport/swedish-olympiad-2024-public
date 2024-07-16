#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int MAXN = 300001;
const ll inf = 1000000007;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

ll n,c;

vl pref, P, C;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    set<int> ss;

    cin >> n >> c;
    ll tot = 0;
    rep(c1,0,n){
        ll a;
        cin >> a;
        P.push_back(a);
    }
    rep(c1,0,n){
        ll a;
        cin >> a;
        tot += a;
        C.push_back(a);
        pref.push_back(tot);
    }
    
    set<pll> S;
    S.insert({inf*inf,n});
    rep(c1,0,n){
        S.insert({pref[c1], c1});
    }

    FT ft(n);

    vl ANS(n,0);
    for(int c1 = n-1; c1 >= 0; c1--){
        ft.update(c1, P[c1]);
        ll x = c-C[c1]+pref[c1];
        pll px = {x, inf};
        auto it = S.lower_bound(px);
        int i = (*it).second;
        ll ans = ft.query(i);
        ANS[c1] = ans;
    }

    trav(y, ANS){
        cout << y << " ";
    }cout << "\n";

    
    return 0;
}