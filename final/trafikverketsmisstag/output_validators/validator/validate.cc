#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long double ld;

#define repe(i, container) for (auto& i : container)

///// TREE PATH SUM CODE
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j, 0, sz(jmp[k]))
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

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
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

struct Tree
{
	vi tree;
	Tree(int n) : tree(n + 1) {}

	void update(int i, int v)
	{
		for (i++; i < tree.size(); i += i & -i)
			tree[i] += v;
	}

	int query(int r)
	{
		int ret = 0;
		for (r++; r > 0; r -= r & -r)
			ret += tree[r];
		return ret;
	}

	int sum(int l, int r)
	{
		if (l) l = query(l - 1);
		return query(r) - l;
	}
};

struct pathsum
{
	int n;
	LCA lc;
	vvi up;
	Tree fenwick;
	vi tin;
	vi tout;
	vi depth;
	pathsum(vvi& edges) : n(edges.size()), lc(edges), fenwick(n * 2), tin(n), tout(n), up(n, vi(19)), depth(n)
	{
		dfs(0, 0, 0, edges);
	}

	void update(int i, int v)
	{
		fenwick.update(tin[i], v);
		fenwick.update(tout[i], -v);
	}

	int timer = 0;
	void dfs(int u, int p, int d, vvi& edges)
	{
		depth[u] = d;
		up[u][0] = p;
		rep(d, 1, 19)
		{
			up[u][d] = up[up[u][d-1]][d-1];
		}

		tin[u] = timer++;
		repe(e, edges[u]) if (e != p) dfs(e, u, d+1, edges);
		tout[u] = timer++;
	}

	int query(int a, int b)
	{
		int lca = lc.lca(a, b);
		int nums = fenwick.query(tin[a]) + fenwick.query(tin[b]) - 2 * fenwick.query(tin[lca]) + fenwick.sum(tin[lca], tin[lca]);
		return nums;
	}
};
/// END OF TREE PATH SUM

void check_isvalid(vi& order, vvi& edges, vector<pii>& squirrels,  feedback_function feedback)
{

  pathsum path(edges);
  for (auto& s : squirrels) path.update(s.first, 1);
  rep(i, 0, order.size())
  {
    pii& sq = squirrels[order[i]];
    path.update(sq.first, -1);
    if (path.query(sq.first, sq.second) > 0) feedback("Squirrel is blocked. x = %d", order[i]);
  }
}

int main(int argc, char **argv) {
  init_io(argc, argv);

  int n, s;
  judge_in >> n >> s;

  vector<vector<int>> edges(n);
  rep(i,0,n-1) {
    int a, b;
    judge_in >> a >> b;
    a--; b--;
    edges[a].emplace_back(b);
    edges[b].emplace_back(a);
  }
  vector<pii> squirrels;
  rep(i,0,s)
  {
    int a,b;
    judge_in >> a >> b;
    a--; b--;
    squirrels.emplace_back(a,b);
  }

  auto check = [&](istream& sol, feedback_function feedback){
    string ans;
    if(!(sol >> ans)) feedback("Expected more output");
    for (char& c : ans) c = (char)toupper(c);
    if(ans != "NO" && ans != "YES")
      feedback("Answer \'%s\' is not {YES|NO}", ans.c_str());

    if(ans == "NO") {
      string trailing;
      if(sol >> trailing) feedback("Trailing output");
      return false;
    }
    vi blocked(n);
    for (auto s : squirrels) blocked[s.first] = 1;

    vi seen(s);
    vi order;
    rep(i,0,s) {
      int x;
      if(!(sol >> x)) feedback("Expected more output");
      x--;
      if(x < 0 || x >= s) feedback("Squirrel x = %d is out of range", x);
      if (seen[x]) feedback("Duplicate squirrel x = %d", x);

      order.push_back(x);

      seen[x] = 1;
    }
    check_isvalid(order,edges,squirrels,feedback);
    

    string trailing;
    if(sol >> trailing) feedback("Trailing output");
    return true;
  };

  bool judge_found_sol = check(judge_ans, judge_error);
  bool author_found_sol = check(author_out, wrong_answer);

  if(!judge_found_sol && author_found_sol)
    judge_error("NO! Solution found an order, but judge says none exists");

  if(judge_found_sol && !author_found_sol)
    wrong_answer("Order exists, but solution did not find it");

  accept();
}
