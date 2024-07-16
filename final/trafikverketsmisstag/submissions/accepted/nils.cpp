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
typedef long double ld;
 
int n,m,k;

const int MAXN = 200001;
const int LOG = 18;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e] < 0)
		low = min(low, val[e] ?: dfs(e,g,f));
 
	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	int n = sz(g);
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

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

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

vector<vi> C;
int spec[MAXN*(LOG+1)] = {0};

int now = 0; 

void add_v(int special){
	vi temp;
	C.push_back(temp);
	spec[now] = special;
	now++;
}
 
void add_edge(int u, int v){
	C[u].push_back(v);
}

vector<vi> tree(MAXN, vi());

int BL[MAXN][LOG] = {0};
int BI[MAXN][LOG] = {0};

int dist[MAXN] = {0};

void dfs1(int i, int par){
    BL[i][0] = par;
    BI[i][0] = i;
    rep(c1,1,LOG){
        BL[i][c1] = BL[BL[i][c1-1]][c1-1];
        BI[i][c1] = now;
        add_v(-1);
        add_edge(BI[i][c1-1], BI[i][c1]);
        add_edge(BI[BL[i][c1-1]][c1-1], BI[i][c1]);
    }

    trav(y, tree[i]){
        if(y != par){
            dist[y] = dist[i]+1;
            dfs1(y, i);
        }
    }
}

void path_edge(int start, int stop, int to){
    for(int c1 = LOG-1; c1 >= 0; c1--){
        int temp = BL[start][c1];
        if(dist[temp] >= dist[stop]){
            add_edge(BI[start][c1], to);
            start = BL[start][c1];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> k;
    rep(c1,0,n-1){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    LCA lca(tree);
    rep(c1,0,n){
        add_v(-1);
    }
    dfs1(0,0);

    rep(c1,0,k){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        add_v(c1);
        add_edge(now-1, a);
        int c = lca.lca(a,b);
        add_edge(c, now-1);
        path_edge(a,c,now-1);
        path_edge(b,c,now-1);
    }

    scc(C,[&](vi& v) {});

    vi n_spec(ncomps, 0);
    bool fail = 0;
    vector<pii> ANS;
    rep(c1,0,now){
        if(spec[c1] != -1){
            n_spec[comp[c1]]++;
            ANS.push_back({comp[c1], spec[c1]+1});
        }
        if(n_spec[comp[c1]] >= 2)fail = 1;
    }

    if(fail){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        sort(all(ANS));
        reverse(all(ANS));
        trav(p, ANS){
            cout << p.second << " ";
        }cout << "\n";
    }

    return 0;
}