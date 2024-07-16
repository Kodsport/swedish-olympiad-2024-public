using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

int n, k;
vector<vector<int>> g;

pair<int,int> dfs(int x, int parent, int guess) {
    int component_size = 1;
    int walls = 0;
    for (auto neighbor : g[x]) {
        if (neighbor == parent) continue;
        auto [csz, w] = dfs(neighbor, x, guess);
        walls += w;
        component_size += csz;
    }
    if (component_size > guess) {
        component_size = 0;
        walls++;
    }
    return {component_size, walls};
}

int main() {
    cin >> n >> k;
    g.resize(n);
    rep(i,1,n) {
        int p; cin >> p; p--;
        g[p].pb(i);
        g[i].pb(p);
    }

    int low = 0, high = n, mid;
    while (high - low > 1) {
        mid = (low + high) / 2;
        auto [csz, w] = dfs(0, -1, mid);
        if (w <= k) high = mid;
        else low = mid;
    }
    cout << high << endl;
}