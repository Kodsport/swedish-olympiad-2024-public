#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#if _MSC_VER > 0
#define deb __debugbreak();
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

vvi nodeindex;

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

void dfs(int u, int p, vvi& treeadj, vi& color, vi& nodes)
{
	if (u != p)
	{
		color[u] ^= 1;
		nodes.push_back(u);
	}

	repe(e, treeadj[u])
	{
		if (e == p) continue;
		dfs(e, u, treeadj, color, nodes);
		nodes.push_back(u);
		color[u] ^= 1;
	}

	if (color[u] != 1 && u != p)
	{
		color[p] ^= 1;
		nodes.push_back(p);
		color[u] ^= 1;
		nodes.push_back(u);
	}
}

int sign(int x)
{
	if (x == 0) return 0;
	if (x > 0) return 1;
	return -1;
}

string getans(vi& nodes, vector<p2>& position)
{
	map<p2, string> difftodir;
	difftodir[p2(1, 0)] = 'V';
	difftodir[p2(-1, 0)] = '^';
	difftodir[p2(0, 1)] = '>';
	difftodir[p2(0, -1)] = '<';
	difftodir[p2(0, 0)] = "";
	string ans = "";
	rep(i, sz(nodes) - 1)
	{
		p2 curr = position[nodes[i]];
		p2 nextu = position[nodes[i + 1]];
		p2 diff = p2(sign(nextu.first - curr.first), sign(nextu.second - curr.second));
		ans += difftodir[diff];
	}
	return ans;
}

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	int r, c;
	int retstart;
	cin >> retstart;
	vector<string> grid(n);
	rep(i, n) cin >> grid[i];
	nodeindex.resize(n, vector<int>(m));
	int ind = 0;
	vector<p2> position;
	rep(i, n) rep(j, m)
	{
		if (grid[i][j] == 'S') r = i, c = j, grid[i][j] = 'X';
	}
	rep(i, n) rep(j, m)
	{
		if (grid[i][j] == 'X') nodeindex[i][j] = ind++, position.emplace_back(i, j);
	}

	vvi edges(ind);
	vector<p2> edgelist;
	rep(i, n) rep(j, m)
	{
		if (grid[i][j] != 'X') continue;
		repe(dir, dirs)
		{
			p2 p = p2(i, j);
			p.first += dir.first;
			p.second += dir.second;
			while (p.first >= 0 && p.second >= 0 && p.first < n && p.second < m)
			{
				if (grid[p.first][p.second] == 'X')
				{
					edgelist.emplace_back(nodeindex[i][j], nodeindex[p.first][p.second]);
					edges[nodeindex[i][j]].push_back(nodeindex[p.first][p.second]);
					break;
				}
				p.first += dir.first;
				p.second += dir.second;
			}
		}
	}

	int qcnt = edges.size();
	UF uf(edges.size());
	vector<p2> treeedges;
	vvi treeadj(edges.size());
	repe(e, edgelist)
	{
		if (uf.find(e.first) != uf.find(e.second))
		{
			uf.merge(e.first, e.second);
			treeedges.emplace_back(e);
			treeadj[e.first].emplace_back(e.second);
			treeadj[e.second].emplace_back(e.first);
		}
	}
	if (uf.size[uf.find(0)] != edges.size())
	{
		cout << "-1\n";
		return 0;
	}

	vi color(qcnt);

	int start = nodeindex[r][c];
	int currp = start;

	vi nodes;
	nodes.push_back(currp);

	dfs(currp, currp, treeadj, color, nodes);

	assert(nodes.back() == start);
	if (color[start] == 0)
	{
		nodes.pop_back();
		color[start] = 1;
	}

	rep(i, qcnt) assert(color[i] == 1);

	/*repe(u, nodes)
	{
		cout << position[u].first << " " << position[u].second << "\n";
	}*/

	string ans = getans(nodes, position);
	cout << ans.size() << "\n";
	cout << ans << "\n";

	return 0;
}
