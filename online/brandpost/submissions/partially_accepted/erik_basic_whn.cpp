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

ll w, h, n;
vpll hydrants;
vvll dp;

void reconstruct_path();

ll inline operator*(const pll& lhs, const pll& rhs) {return llabs(lhs.first - rhs.first) + llabs(lhs.second - rhs.second);}

ll get_water(ll x, ll y) {
    const pll pos = mp(x, y);
    ll C = 0;
    rep(k, 0, n) {
        C += max<ll>(0, 1 + x + y - (pos * hydrants[k]));
    }
    return C;
}

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

    dp.resize(w);
    rep(i, 0, w) dp[i].resize(h);

    rep(i, 0, w) {
        rep(j, 0, h) {
            if (i != 0) {
                if (j != 0) {
                    dp[i][j] = min<ll>(dp[i - 1][j], dp[i][j - 1]) + get_water(i, j);
                } else {
                    dp[i][j] = dp[i - 1][j] + get_water(i, j);
                }
            } else {
                if (j != 0) {
                    dp[i][j] = dp[i][j - 1] + get_water(i, j);
                } else {
                    dp[i][j] = get_water(0, 0);
                }
            }
        }
    }

    cout << dp[w - 1][h - 1] << endl;

    //reconstruct_path();

    return 0;
}

void reconstruct_path() {
    // reconstruct best route
    ll x = w - 1;
    ll y = h - 1;
    while (x + y) {
        if (x) {
            if (y) {
                if (dp[x - 1][y] <= dp[x][y - 1]) {
                    x--;
                    cout << "R";
                } else {
                    y--;
                    cout << "U";
                }
            } else {
                x--;
                cout << "R";
            }
        } else {
            y--;
            cout << "U";
        }
    }
    cout << endl;
}