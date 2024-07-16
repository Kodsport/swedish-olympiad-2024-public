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

const int MAXN = 100001;
const ll inf = 1000000007;

vl W;
vl gaps;
int n,k;

double DP2[MAXN][2] = {0};
ll USES[MAXN][2] = {0};
int DPC2[MAXN][2] = {0};
int cc2 = 0;

pair<double, ll> dp2(int i, bool last, double c){
    if(i == n)return {0,0};
    if(DPC2[i][last] == cc2)return {DP2[i][last], USES[i][last]};
    pair<double, ll> temp1 = dp2(i+1, 0, c);
    double extra = W[i]-c;
    if(last == 1)extra -= gaps[i-1];
    pair<double, ll> temp2 = dp2(i+1, 1, c);
    temp2.first += extra;
    temp2.second++;
    if(temp1.first < temp2.first)swap(temp1, temp2);
    DPC2[i][last] = cc2;
    DP2[i][last] = temp1.first;
    USES[i][last] = temp1.second;
    return temp1;
}

ll alien(){
    double lo = -inf;
    double hi = inf;
    rep(_,0,300){
        double mid = (lo+hi)/2;
        cc2++;
        pair<double, ll> p = dp2(0, 0, mid);
        if(p.second == k)return round(mid*double(k) + p.first);
        if(p.second > k)lo = mid;
        if(p.second < k)hi = mid;
    }
    cc2++;
    pair<double, ll> p = dp2(0, 0, lo);
    return round(lo*double(k) + p.first);
}

vl X, B;

vector<vector<pll> > LB(MAXN, vector<pll>());
vector<vector<pll> > RB(MAXN, vector<pll>());

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    rep(c1,0,n){
        ll a;
        cin >> a;
        X.push_back(a);
    }
    rep(c1,0,n){
        ll a;
        cin >> a;
        B.push_back(a);
        W.push_back(0);
    }
    rep(c1,0,n-1){
        gaps.push_back(0);
    }

    rep(c1,0,n){
        vl H;
        ll a;
        rep(c2,0,B[c1]){
            cin >> a;
            H.push_back(a);
        }
        rep(c2,0,B[c1]){
            cin >> a;
            W[c1] += abs(a);
            if(a < 0){
                LB[c1].push_back({H[c2],-a});
            }
            else{
                RB[c1].push_back({H[c2], a});
            }
        }
        sort(all(LB[c1]));
        sort(all(RB[c1]));
    }

    // can be done in O(n):
    rep(c1,0,n-1){
        ll d = X[c1+1]-X[c1]-1;
        trav(b1, RB[c1]){
            ll overlap = 0;
            trav(b2, LB[c1+1]){
                assert(b1.first != b2.first);
                assert(max(b1.second, b2.second) <= d);
                if(b1.first > b2.first)overlap = max(overlap, b1.second+b2.second-d);
            }
            W[c1+1] += overlap;
            gaps[c1] += overlap;
        }
        trav(b2, LB[c1+1]){
            ll overlap = 0;
            trav(b1, RB[c1]){
                if(b2.first > b1.first)overlap = max(overlap, b1.second+b2.second-d);
            }
            W[c1] += overlap;
            gaps[c1] += overlap;
        }
    }

    cout << alien() << "\n";
    
    return 0;
}