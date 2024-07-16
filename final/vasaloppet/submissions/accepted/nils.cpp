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
typedef long double ld;
 
int n;
ll T,S;
const int MAXN = 100001;

vl A,B;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> T >> S;

    rep(c1,0,n){
        ll a,b;
        cin >> a >> b;
        A.push_back(a);
        B.push_back(b);
        if(b-a >= S){
            cout << "0\n";
            return 0;
        }

    }
    ll ans = S;

    ll inside = 0;
    int p = 0;
    rep(c1,0,n){
        ll r = A[c1]+S;
        ll extra = 0;
        while(p < n && B[p] <= r){
            inside += B[p]-A[p];
            p++;
        }
        if(p < n && A[p] < r)extra = r-A[p];
        ans = min(ans, S-(extra+inside));
        inside -= B[c1]-A[c1];
    }

    cout << ans << "\n";

    return 0;
}