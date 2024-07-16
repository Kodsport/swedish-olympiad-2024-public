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

vector<pii> dirs = {{0,1},{0,-1},{-1,0},{1,0}};

bool valid(vvi& answer){
	int n = sz(answer[0]);
	rep(i,0,3)
	{
		rep(j,0,n)
		{
			vi neighbours;
			for(auto& delta:dirs)
			{
				pii pos = pii(i+delta.first,j+delta.second);
				if (pos.first<0||pos.first>=3||pos.second<0||pos.second>=n) continue;
				neighbours.push_back(answer[pos.first][pos.second]);
			}

			int v = answer[i][j];
			if (v>1)
			{
				bool lessexists = 0;
				rep(k, 0, sz(neighbours)) lessexists |= neighbours[k]==v-1;
				if (!lessexists) return false;
			}
			if (v<n*3)
			{
				bool greaterexists = 0;
				rep(k, 0, sz(neighbours)) greaterexists |= neighbours[k]==v+1;
				if (!greaterexists) return false;
			}
		}
	}

	
	return true;
}

int main(int argc, char **argv) {
	init_io(argc, argv);
	

	int n;
	judge_in >> n;

	vvi grid(3, vi(n));

	rep(i,0,3){
		rep(j,0,n){
			judge_in >> grid[i][j];
		}
	}

	auto check = [&](istream& sol, feedback_function feedback)
	{
		vi seen(n*3+1);
		vvi ans(3, vi(n));

		rep(i,0,3){
			rep(j,0,n){
				int v;
				sol >> v;
				if (v<=0||v>n*3) feedback("Segment index out of range");
				ans[i][j] = v;
				assert(!seen[v]);
				seen[v] = 1;

				if (grid[i][j]!=0&&ans[i][j]!=grid[i][j]) feedback("Answer changed input index of snake segment");
			}
		}

		string trailing;
		if(sol >> trailing) feedback("Trailing output");

		if (!valid(ans)) feedback("Invalid solution");

		return ans;
	};

	check(judge_ans, judge_error);
	check(author_out, wrong_answer);

	accept();
}
