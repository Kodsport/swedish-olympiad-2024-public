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

vl  P, C;
ll ANS[MAXN] = {0};

struct interval{
    int lo,hi;
    ll lazy_p = 0;
    ll lazy_c = 0;
    set<pll> S;

    interval(int lo, int hi): lo(lo), hi(hi){}

    vector<pll> geq(ll c){
        vector<pll> res;
        while(1){
            if(sz(S) == 0)break;
            auto it = S.end();
            it--;
            if((*it).first + lazy_c >= c){
                int i = (*it).second;
                ANS[i] += lazy_p;
                res.push_back({(*it).first + lazy_c, i});
                S.erase(it);
            }
            else{
                break;
            }
        }
        return res;
    }

    vector<pll> leq(ll c){
        vector<pll> res;
        while(1){
            if(sz(S) == 0)break;
            auto it = S.begin();
            if((*it).first + lazy_c <= c){
                int i = (*it).second;
                ANS[i] += lazy_p;
                res.push_back({(*it).first + lazy_c, i});
                S.erase(it);
            }
            else{
                break;
            }
        }
        return res;
    }
};

ll n,m;

vector<interval> I;

int find_interval(ll c){
    rep(c1,0,sz(I)){
        if(I[c1].lo <= c && c <= I[c1].hi)return c1;
    }
    return -1;
}

void ins(ll c, ll i){
    int j = find_interval(c);
    ANS[i] -= I[j].lazy_p;
    I[j].S.insert({c-I[j].lazy_c, i});
}

void lazy_shift(interval &inter, ll c, ll p){
    inter.lazy_c -= c;
    inter.lazy_p += p;
    vector<pll> res = inter.leq(inter.lo-1);
    trav(p, res){
        ins(p.first, p.second);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    rep(c1,0,n){
        ll a;
        cin >> a;
        P.push_back(a);
    }

    rep(c1,0,n){
        ll a;
        cin >> a;
        C.push_back(a);
    }
    
    ll a = 0;
    ll b = 10;

    while(a <= inf){
        interval temp(a, b);
        I.push_back(temp);
        a = b+1;
        b *= 2;
    }

    rep(c1,0,n){
        ins(m, c1);

        int j = find_interval(C[c1]);
        vector<pll> res = I[j].geq(C[c1]);
        trav(p, res){
            ANS[p.second] += P[c1];
            ins(p.first-C[c1],p.second);
        }
        rep(c2,j+1,sz(I)){
            lazy_shift(I[c2], C[c1], P[c1]);
        }
    }

    trav(inter, I){
        trav(p, inter.S){
            ANS[p.second] += inter.lazy_p;
        }
    }

    rep(c1,0,n){
        cout << ANS[c1] << " ";
    }cout << "\n";

    return 0;
}