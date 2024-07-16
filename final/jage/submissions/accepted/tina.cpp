#ifdef LOCAL
    #pragma GCC optimize("Ofast,unroll-loops") // O3 for geo
    #pragma GCC target("avx2,sse4.2,lzcnt,popcnt,bmi,bmi2")
#endif

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<ll> vll;

const int MOD = 1e9 + 7; // 998244353; 
const int maxN = 1e5 + 5;

#define fuck(x) cout << #x << " " << x << "\n"

#define ff first
#define ss second

void setIO() {
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
}

// void fin() {
//     freopen("a.in", "r", stdin);
//     freopen("a.out", "w", stdout);
// }

int n, q;
vector<string> ppl;
vector<bool> hunt;
map<string, int> cor;

int main() {
	setIO();

    cin >> n >> q;
    ppl.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> ppl[i];
        cor[ppl[i]] = i;
    }
    hunt.resize(n, 0);
    hunt[0] = 1;

    set<string> cheaters;
    while(q--) {
        string s1, temp, s2;
        cin >> s1 >> temp >> s2;
        if(!hunt[cor[s1]]) cheaters.insert(s1);
        hunt[cor[s1]] = 0;
        hunt[cor[s2]] = 1;
    }

    cout << cheaters.size() << "\n";
    for(auto v : cheaters) cout << v << " ";
    cout << "\n";

    return 0;
}