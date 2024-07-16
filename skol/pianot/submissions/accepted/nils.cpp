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

const int MAXL = 15;
const int inf = 1e9;

int DP[(1 << MAXL)] = {0};
int cost[MAXL][MAXL] = {0};
string song;
int n,m;
map<char,int> compress;

bool bit_in_mask(int mask, int i){
    return ((mask & (1 << i)) != 0);
}

int penalty(int mask){
    int res = 0;
    rep(c1,0,m){
        rep(c2,0,m){
            if(bit_in_mask(mask, c1) && !bit_in_mask(mask, c2)){
                res += cost[c1][c2];
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> song;
    n = sz(song);
    m = 0;
    rep(c1,0,n){
        if(compress.find(song[c1]) == compress.end()){
            compress[song[c1]] = m;
            m++;
        }
        if(c1 > 0){
            int a = compress[song[c1-1]];
            int b = compress[song[c1]];
            cost[a][b]++;
            cost[b][a]++;
        }
    }

    for(int mask = (1 << m)-2; mask >= 0; mask--){
        DP[mask] = inf;
        rep(i,0,m){
            if(!bit_in_mask(mask, i)){
                DP[mask] = min(DP[mask], DP[(mask|(1 << i))]);
            }
        }
        DP[mask] += penalty(mask);
    }

    cout << DP[0] << "\n";
 
    return 0;
}