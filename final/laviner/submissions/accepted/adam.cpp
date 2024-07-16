#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define ar array
#define vo vector
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

#define rep(i, a, b) for(ll i=(a); i<(b); i++) 
#define repd(i, a, b) for(ll i=(a); i>=(b); i--) 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vo<vo<int>> al(n, vo<int>());
    rep(i, 0, n-1) {
        int a;
        cin >> a, --a;

        al[a].pb(i+1);
    }

    auto dfs=[&](int u, int mid, auto&& dfs) -> ar<int, 2> {
        int sz=1, cnt=0;
        for(auto v: al[u]) {
            auto [a, b]=dfs(v, mid, dfs);
            sz+=a; cnt+=b;
        }

        if(sz>mid) 
            return ar<int, 2>{0, cnt+1};

        return ar<int, 2>{sz, cnt};
    };

    int lo=0, hi=n, ans=n;
    while(lo<=hi) {
        int mid=lo+(hi-lo)/2;

        auto [ignore, cnt]=dfs(0, mid, dfs);

        (cnt<=k)?hi=mid-1,ans=mid:lo=mid+1;
    }

    cout << ans;
}
