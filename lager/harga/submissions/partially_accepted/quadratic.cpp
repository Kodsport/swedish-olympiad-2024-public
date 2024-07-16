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

const int MAXN = 3001;
const int inf = 1000000007;

int n,m;
int F[MAXN] = {0};
int X[MAXN] = {0};

int indeg[MAXN] = {0};

bool possible[MAXN] = {0};

int F2[MAXN] = {0};
bool on_chain[MAXN] = {0};
int remap[MAXN] = {0};

vector<vi> cycles(MAXN, vi());
int in_cyc[MAXN] = {0};
int ind[MAXN] = {0};
int now = 0;

void setup_cycles(){
    rep(c1,0,m){
        in_cyc[c1] = -1;
    }
    rep(c1,0,m){
        if(in_cyc[c1] == -1){
            vi temp;
            cycles.push_back(temp);
            int i = c1;
            while(in_cyc[i] == -1){
                in_cyc[i] = now;
                ind[i] = sz(cycles[now]);
                cycles[now].push_back(i);
                i = F[i];
            }
            now++;
        }
    }
}

// jump in the permutation
// (can use binary lifting too)
int perm(int i, int x){
    int cl = sz(cycles[in_cyc[i]]);
    return cycles[in_cyc[i]][(ind[i] + x)%cl];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    //assert(n <= 10000 && m <= 10000);
    rep(c1,0,n){
        int a;
        cin >> a;
        a--;
        X[c1] = a;
        possible[c1] = 1;
    }
    rep(c1,0,m){
        int a;
        cin >> a;
        a--;
        F[c1] = a;
        indeg[a]++;
    }

    int zeros = 0;
    int zero = -1;
    rep(c1,0,m){
        if(indeg[c1] == 0){
            zeros++;
            zero = c1;
        }
    }

    // can't reach > 1 zero
    if(zeros > 1){
        cout << "-1\n";
        return 0;
    }

    int chain = 0;

    if(zeros == 1){
        int zero1 = zero;
        // one zero, simulate a bit to get rid of it
        while(indeg[zero] == 0){
            chain++;
            on_chain[zero] = 1;
            zero = F[zero];
            indeg[zero]--;
        }

        // must visit everything on chain
        rep(c1,0,n){
            rep(c2,0,chain){
                int j = (c1+c2)%n;
                if(X[j] != zero1)possible[c1] = 0;
            }
        }

        rep(c2,0,chain){
            int x0 = X[0];
            rep(c1,0,n-1){
                X[c1] = F[X[c1+1]];
            }
            X[n-1] = F[x0];
        }

        // remap to the permutation
        int tmp = 0;
        rep(c1,0,m){
            if(!on_chain[c1]){
                remap[c1] = tmp;
                tmp++;
            }
        }
        rep(c1,0,m){
            if(!on_chain[c1])F2[remap[c1]] = remap[F[c1]];
        }
        rep(c1,0,n){
            X[c1] = remap[X[c1]];
        }
        rep(c1,0,m-chain){
            F[c1] = F2[c1];
        }
        m -= chain;
    }

    setup_cycles();
    vector<vi> LL(m, vi());

    rep(c1,0,n*m+3){
        int x = perm(X[c1%n],c1);
        LL[x].push_back(c1);
    }
    rep(c1,0,m){
        reverse(all(LL[c1]));
    }

    vi ANS;

    rep(c1,0,n){
        int ma = -1;
        rep(c2,0,m){
            if(sz(LL[c2]) == 0){
                ma = inf;
            }
            else{
                ma = max(ma, LL[c2].back());
            }
        }
        if(ma == inf || possible[c1] == 0){
            cout << "-1\n";
            return 0;
        }
        else{
            ANS.push_back(chain + ma - c1 + 1);
        }
        int x = perm(X[c1%n],c1);
        LL[x].pop_back();
    }

    trav(y, ANS){
        cout << y << " ";
    }
    cout << "\n";

    return 0;
}