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
const int inf = 1000000007;

struct permutation{
    vi P, in_cyc, ind;
    vector<vi> cycles;
    int len;

    permutation(vi p){
        P = p;
        len = sz(P);
        rep(c1,0,len){
            in_cyc.push_back(-1);
            ind.push_back(-1);
        }
        rep(c1,0,len){
            if(in_cyc[c1] == -1){
                vi cycle;
                int now = sz(cycles);
                int a = c1;
                while(in_cyc[a] == -1){
                    in_cyc[a] = now;
                    ind[a] = sz(cycle);
                    cycle.push_back(a);
                    a = P[a];
                }
                cycles.push_back(cycle);
            }
        }
    }

    int jump(int i, int steps){
        int siz = sz(cycles[in_cyc[i]]);
        return cycles[in_cyc[i]][(ind[i]+steps+siz)%siz];
    }

    permutation exponentiate(int k){
        vi P2(len, -1);
        rep(c1,0,len){
            P2[c1] = jump(c1, k);
        }
        permutation new_p(P2);
        return new_p;
    }
};

int n,m;
vi F,X,Y;

int indeg[MAXN] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    rep(c1,0,n){
        int a;
        cin >> a;
        a--;
        X.push_back(a);
    }

    rep(c1,0,m){
        int a;
        cin >> a;
        a--;
        F.push_back(a);
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

    // not a permutation:
    if(zeros > 1){
        cout << "-1\n";
        return 0;
    }
    if(zeros == 1){
        bool fail = 0;
        rep(c1,0,n){
            if(X[c1] != zero)fail = 1;
        }

        vi mark(m, 0);
        int seen = 0;
        while(mark[zero] == 0){
            mark[zero] = 1;
            seen++;
            zero = F[zero];
        }

        if(seen != m)fail = 1;

        if(fail){
            cout << "-1\n";
        }
        else{
            rep(c1,0,n){
                cout << m << " ";
            }cout << "\n";
        }
        return 0;
    }

    // F is a permutation:

    permutation pi(F);
    permutation sigma = pi.exponentiate(n);

    rep(c1,0,n){
        Y.push_back(pi.jump(X[c1], c1));
    }

    vl starts;
    vector<vl> start_times(m, vl());
    vi mark(m, 0);
    int seen = 0;

    rep(c1,0,n){
        start_times[Y[c1]].push_back(c1+1);
        if(mark[Y[c1]] == 0){
            mark[Y[c1]] = 1;
            seen++;
            starts.push_back(Y[c1]);
        }
    }

    set<pll> S;
    vl visit_time(m, -1);
    vl chain(m,0);
    vl original_time(m,0);
    trav(y, starts){
        reverse(all(start_times[y]));
        int z = sigma.jump(y, 1);
        ll ch = 0;
        ll penalty = start_times[y].back();
        visit_time[y] = penalty;
        original_time[y] = penalty;
        S.insert({-penalty, y});

        while(mark[z] == 0){
            mark[z] = 1;
            seen++;
            ch++;
            visit_time[z] = ch*ll(n) + visit_time[y];
            original_time[z] = visit_time[z];
            S.insert({-visit_time[z], z});
            z = sigma.jump(z, 1);
        }
        chain[y] = ch;
    }

    if(seen != m){
        // not every bar reachable
        cout << "-1\n";
        return 0;
    }

    vl ANS;
    rep(c1,0,n){
        ll ans = -(*(S.begin())).first;
        ANS.push_back(ans-c1);
        int y = Y[c1];
        S.erase({-visit_time[y], y});
        start_times[y].pop_back();

        if(sz(start_times[y]) > 0){
            visit_time[y] = start_times[y].back();
        }
        else{
            int z = sigma.jump(y, -1);
           // visit_time[y] = original_time[y]; // tricky special case when z == y...
            visit_time[y] = n + original_time[z];
        }
        S.insert({-visit_time[y], y});

    }
    
    rep(c1,0,n){
        cout << ANS[c1] << " ";
    }cout << "\n";

    return 0;
}