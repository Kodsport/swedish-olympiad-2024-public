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

    ll n;
    cin >> n;

    ll lo=1, hi=min(n, 100000ll), ans=1;
    while(lo<=hi) {
        ll mid=lo+(hi-lo)/2;
        (mid*mid*mid+3*mid*mid+2*mid<n)?ans=mid,lo=mid+1:hi=mid-1;
    }

    cout << ans;
}
