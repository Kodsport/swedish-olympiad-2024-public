#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <set>
#include <map>

using namespace std;

typedef long long int ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;

#define rep(i, a, b) for (ll i = a; i < b; i++)
#define sz(a) (ll) a.size()
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define trav(i, a, t) for (t::iterator i = a.begin(); i != a.end(); i++)

const ll MAXD = 200;

ll w, h, n;
vpll hydrants;
vvll dp;

struct cell {
    ll U, D, L, R;
    ll diff;
    ll cnt;
    cell() {U = 0; D = 0; L = 0; R = 0; cnt = 0; diff = 0;}
    cell(ll U, ll D, ll L, ll R, ll diff, ll cnt) : U(U), D(D), L(L), R(R), diff(diff), cnt(cnt) {diff += U + D + L + R; cnt += diff;}
    void inline step() {
        diff += U + D + L + R;
        cnt += diff;
    }
    void inline raise(const cell* below) {
        diff = below->diff;
        cnt = below->cnt;
        step();
    }
};

cell sim[2 * MAXD - 1][MAXD][MAXD]; // [time][x][y] --> cell

void visualize();

int main() {
    cin.tie(NULL)->sync_with_stdio(false);

    cin >> w >> h >> n;
    hydrants.resize(n);
    rep(i, 0, n) {
        ll tmpx, tmpy;
        cin >> tmpx >> tmpy;
        tmpx--; tmpy--;
        hydrants[i] = mp(tmpx, tmpy);
    }

    // simulate water-flow

    rep(k, 0, n) sim[0][hydrants[k].second][hydrants[k].first] = cell(1, 1, 1, 1, 1, 1);

    rep(t, 1, w + h - 1) {        
        rep(i, 0, h) {
            rep(j, 0, w) {
                cell* oth;

                if (i != 0) { // pull from [i - 1][j]
                    sim[t][i][j].D += sim[t - 1][i - 1][j].D;
                }
                if (i != h - 1) { // pull from [i + 1][j]
                    sim[t][i][j].U += sim[t - 1][i + 1][j].U;
                }
                if (j != 0) { // pull from [i][j - 1]
                    oth = &sim[t - 1][i][j - 1];
                    sim[t][i][j].R += oth->R + ((oth->U + oth->D) * (t != 1));
                }
                if (j != w - 1) { // pull from [i][j + 1]
                    oth = &sim[t - 1][i][j + 1];
                    sim[t][i][j].L += oth->L + ((oth->U + oth->D) * (t != 1));
                }

                // pull from self [i][j]
                oth = &sim[t - 1][i][j];
                sim[t][i][j].raise(oth);
            }
        }
    }

    // calculate dp

    dp.resize(h);
    rep(i, 0, h) dp[i].resize(w);

    rep(i, 0, h) {
        rep(j, 0, w) {
            if (i != 0) {
                if (j != 0) {
                    dp[i][j] = min<ll>(dp[i - 1][j], dp[i][j - 1]) + sim[i + j][i][j].cnt;
                } else {
                    dp[i][j] = dp[i - 1][j] + sim[i + j][i][j].cnt;
                }
            } else {
                if (j != 0) {
                    dp[i][j] = dp[i][j - 1] + sim[i + j][i][j].cnt;
                } else {
                    dp[i][j] = sim[i + j][i][j].cnt;
                }
            }
        }
    }

    cout << dp[h - 1][w - 1] << endl;
    
    return 0;
}

// a cell has 4 propagations: spread right, spread left, branch down, branch up
// a cell also has a default increase
// and a count

//     | AU |
// ----+----+----
// ALUD|    |ARUD
// ----+----+----
//     | AD |    