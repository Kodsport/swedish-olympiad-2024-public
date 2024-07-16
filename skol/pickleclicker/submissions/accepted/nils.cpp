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

const int MAXN = 100001;
const int inf = 1e9;

int n,t;
vi P,C;

int money[MAXN][2] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> t;
    rep(c1,0,n){
        int p,c;
        cin >> p >> c;
        P.push_back(p);
        C.push_back(c);
    }

    int max_rate = P[0];
    rep(c1,0,MAXN){
        rep(c2,0,2){
            money[c1][c2] = -inf;
        }
    }
    money[P[0]][1] = P[0];

    if(P[0] >= t){
        cout << "1\n";
        return 0;
    }

    rep(day, 2, MAXN){
        int max_rate2 = max_rate;
        rep(rate, P[0], max_rate+1){
            int m = money[rate][(day+1)%2];
            money[rate][day%2] = max(money[rate][day%2], m + rate);
            rep(i, 0, n){
                if(C[i] <= m){
                    money[rate + P[i]][day%2] = max(money[rate + P[i]][day%2], m + rate + P[i] - C[i]);
                    max_rate2 = max(max_rate2, rate + P[i]);
                }
            }
        }
        int max_money = 0;
        rep(rate, P[0], max_rate2+1){
            max_money = max(max_money, money[rate][day%2]);
        }
        if(max_money >= t){
            cout << day << "\n";
            break;
        }
        max_rate = max_rate2;
    }
 
    return 0;
}