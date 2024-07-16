#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<pi> vpi;
typedef vector<vi> vvi;
const int inf = 0x3f3f3f3f;
const ll linf = 1234567890123456789;
const ll mod = 1000000007;
#define all(x) x.begin(), x.end()
#define debug(x) cerr << (#x) << " = " << (x) << endl
#define sz(x) ((int)(x).size())
#define rep(i, a, b) for(int i = a; i < (b); ++i)

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/RMQ.h
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/LCA.h
struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vpi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vpi>& C, int v, int par) {
		time[v] = T++;
		for (auto [y,_] : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
};

int n;
vector<vpi> adj;
vi up, down, depth;

void dfs(int u, int c_up, int c_down, int d, int p){
    up[u] = c_up;
    down[u] = c_down;
    depth[u] = d;
    for(auto [v, dir] : adj[u]){
        if(v == p) continue;
        dfs(v, dir?0:c_up+1, dir?c_down+1:0, d+1, u);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    adj = vector<vpi>(n);
    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v, 1);
        adj[v].emplace_back(u, 0);
    }
    up = down = depth = vi(n);
    dfs(0, 0, 0, 0, -1);
    LCA lca(adj);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        a--,b--;
        int c = lca.lca(a, b);
        if(depth[a]-depth[c] <= up[a] && depth[b]-depth[c] <= down[b]){
            cout << "ja\n";
        }
        else{
            cout << "nej\n";
        }
    }
}
