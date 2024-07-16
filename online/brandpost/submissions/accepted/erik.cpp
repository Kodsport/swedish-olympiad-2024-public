#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

typedef long long int ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef set<pll> spll;

#define rep(i, a, b) for (ll i = a; i < b; i++)
#define sz(a) (ll) a.size()
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define trav(i, a, t) for (t::iterator i = a.begin(); i != a.end(); i++)

ll floor2(ll x) {
    if (x >= 0) return x / 2;
    return (x - 1) / 2;
}

ll w, h, n;

struct pt {
    ll x, y;
    pt(ll x, ll y) : x(x), y(y) {}
    pt() {}
};

vector<pt> hydrants;

ll inline operator*(const pt& lhs, const pt& rhs) {return llabs(lhs.x - rhs.x) + llabs(lhs.y - rhs.y);}

ll get_water(ll y, ll x) { // O(n)
    const pt pos = pt(x, y);
    ll C = 0;
    rep(k, 0, n) {
        C += max<ll>(0, 1 + x + y - (pos * hydrants[k]));
    }
    return C;
}

vvll dp;

vvll water;
vvll delta;

void visualize_water();

int main() {
    cin.tie(NULL)->sync_with_stdio(false);

    cin >> w >> h >> n;
    dp.resize(h);
    water.resize(h);
    delta.resize(h);
    rep(i, 0, h) {
        dp[i].resize(w);
        water[i].resize(w);
        delta[i].resize(w, 0);
    }
    hydrants.resize(n);
    rep(k, 0, n) {
        ll tmpx, tmpy;
        cin >> tmpx >> tmpy;
        tmpx--; tmpy--;
        hydrants[k] = pt(tmpx, tmpy);
    }

    // calc delta
    rep(i, 0, h) {
        rep(k, 0, n) {
            // consider the x value such that:
            // i + x = hydrants[k].second - x + |hydrants[k].first - i|
            // assuming x <= hydrants[k].second
            // 2x = hydrants[k].second - i + |hydrants[k].first - i|;
            // this gives the x value for the cell (x, i) at equal distance from origin and hydrant[k]
            // ciel(x) and floor(x) + 1 gives the cells which should recieve delta...

            // now I have implemented by own 'divide by 2 and take floor' function floor2
            // which most importantly works for negative inputs

            if (hydrants[k].x + i >= llabs(i - hydrants[k].y)) { // distance to (x, i) from (0, 0) versus hydrant[k]
                // i + x = |i - hydrants[k].first| - (hydrants[k].first - i - x)
                ll xx = hydrants[k].x - i + llabs(i - hydrants[k].y);
                delta[i][max<ll>(0, floor2(xx + 1))]++;
                if (xx < 2 * (w - 1)) delta[i][max<ll>(0, floor2(xx) + 1)]++;
                if (hydrants[k].x != w - 1) delta[i][hydrants[k].x + 1] -= 2;
            }
        }
    }

    // calc water
    rep(i, 0, h) {
        // calc initial column...
        water[i][0] = get_water(i, 0);
        ll d = delta[i][0];
        // apply delta
        rep(j, 1, w) {
            d += delta[i][j];
            water[i][j] = water[i][j - 1] + d;
        }
    }

    // visualize_water();

    // calc dp
    rep(i, 0, h) {
        rep(j, 0, w) {
            if (i != 0) {
                if (j != 0) {
                    dp[i][j] = min<ll>(dp[i - 1][j], dp[i][j - 1]) + water[i][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + water[i][j];
                }
            } else {
                if (j != 0) {
                    dp[i][j] = dp[i][j - 1] + water[i][j];
                } else {
                    dp[i][j] = water[i][j];
                }
            }
        }
    }

    cout << dp[h - 1][w - 1] << endl;

    return 0;
}