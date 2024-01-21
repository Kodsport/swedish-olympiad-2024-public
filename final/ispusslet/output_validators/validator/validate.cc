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

void check_isvalid(string& moves, vector<string> grid, int return_start, feedback_function feedback)
{
	int n = grid.size();
	int m = grid[0].size();
	vvi nodeindex(n,vi(m,-1));
	pii o = pii(-1,-1);
	rep(i,0,n) rep(j,0,m) if(grid[i][j]=='S') o=pii(i,j), grid[i][j]='X';
	int ind = 0;
	rep(i,0,n) rep(j,0,m) if (grid[i][j]=='X') nodeindex[i][j]=ind++;
	int cnt = ind;

	vvi edges(cnt, vi(4,-1));
	// down up left right
	vector<pii> directions = {{1,0},{-1,0},{0,-1},{0,1}};
	map<char,int> movetodir;
	movetodir['V']=0;
	movetodir['v']=0;
	movetodir['^']=1;
	movetodir['<']=2;
	movetodir['>']=3;
	rep(i,0,n) rep(j,0,m)
	{
		if (nodeindex[i][j]==-1) continue;
		int me = nodeindex[i][j];
		rep(k,0,4)
		{
			pii dir = directions[k];
			pii pos = pii(i+dir.first,j+dir.second);
			while (pos.first>=0&&pos.second>=0&&pos.first<n&&pos.second<m)
			{
				if (nodeindex[pos.first][pos.second]!=-1)
				{
					edges[me][k] = nodeindex[pos.first][pos.second];
					break;
				}
				pos.first+=dir.first;
				pos.second+=dir.second;
			}
		}
	}

	vi color(cnt);
	int start = nodeindex[o.first][o.second];
	int currp = start;
	rep(i,0,moves.size())
	{
		if (movetodir.find(moves[i])==movetodir.end()) feedback("Unknown move %c", moves[i]);
		int dir = movetodir[moves[i]];
		if (edges[currp][dir]==-1)
		{
			bool allwhite = 1;
			rep(j,0,cnt) allwhite&= color[j];
			if (!allwhite) feedback("Not all are circles");
			if (return_start) feedback("Crashed into wall while need to return");
			return;
		}
		currp = edges[currp][dir];
		color[currp] ^= 1;
	}

	bool allwhite = 1;
	rep(j,0,cnt) allwhite&= color[j];
	if (!allwhite) feedback("Not all are circles");
	if (return_start&&(currp!=start)) feedback("Did not return to start");
}

const int MAX_MOVES = int(1e5);
int main(int argc, char **argv) {
	init_io(argc, argv);

	int n, m, return_start;
	judge_in >> n >> m >> return_start;
	vector<string> grid(n);
	for (int i = 0; i < n; i++) judge_in >> grid[i];


	auto check = [&](istream& sol, feedback_function feedback){
		int ans;
		if(!(sol >> ans)) feedback("Expected more output");
		if (ans==-1)
		{
			string trailing;
			if(sol >> trailing) feedback("Trailing output");
			return false;
		}
		if (ans>MAX_MOVES) feedback("Too many moves");
		string moves;
		if(!(sol >> moves)) feedback("Expected more output (moves)");
		if (moves.size()!=ans) feedback("Length and moves did not match. Expected %d, got %d", ans, int(moves.size()));

		check_isvalid(moves, grid, return_start, feedback);

		string trailing;
		if(sol >> trailing) feedback("Trailing output");
		return true;
	};

	bool judge_found_sol = check(judge_ans, judge_error);
	bool author_found_sol = check(author_out, wrong_answer);

	if(!judge_found_sol && author_found_sol)
		judge_error("NO! Solution found valid moves, but judge says none exists");

	if(judge_found_sol && !author_found_sol)
		wrong_answer("Valid moves exists, but solution did not find it");

	accept();
}
