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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

ll n,m;

vl prefC, prefP, P, C;

int next_leq(RMQ<ll> &rmq, int i, ll c){
    int lo = i;
    int hi = n+1;
    while(lo < hi-1){
        int mid = (lo+hi) / 2;
        if(rmq.query(i, mid) <= c){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    return lo;
}

ll solve(RMQ<ll> &rmq, int i){
    ll c = m;
    ll ans = 0;

    while(i < n && c > 0){
        int lo = i-1;
        int hi = n;
        while(lo < hi-1){
            int mid = (lo+hi)/2;
            ll pc = prefC[mid+1] - prefC[i];
            if(pc > c){
                hi = mid;
            }
            else{
                lo = mid;
            }
        }
        ans += prefP[lo+1] - prefP[i];
        c -= prefC[lo+1] - prefC[i];
        i = lo+1;

        if(i < n)i = next_leq(rmq, i, c);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;//assert(n <= 1000);

    ll tot = 0;
    prefP.push_back(0);
    rep(c1,0,n){
        ll a;
        cin >> a;
        tot += a;
        P.push_back(a);
        prefP.push_back(tot);
    }

    tot = 0;
    prefC.push_back(0);
    rep(c1,0,n){
        ll a;
        cin >> a;
        tot += a;
        C.push_back(a);
        prefC.push_back(tot);
    }
    
    RMQ<ll> rmq(C);
    
    rep(c1,0,n){
        ll temp = solve(rmq, c1);
        cout << temp << " ";
    }cout << "\n";

    return 0;
}