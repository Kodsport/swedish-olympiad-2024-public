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



bool valid(vi &answer, vvi &signs, int size, int m){
	
	rep(j,0,m){
		rep(i,0,size-1){
			if (signs[answer[i]-1][j] >= signs[answer[i+1]-1][j]) continue;
			return false;
		}
	}

	return true;
}

bool valid_normalized(vi &answer, vvi &signs, int n, int m){

	// Efter att vi har normaliserad måste alla värden vara mellan 0 och 1.

	vvi normalized;

	rep(i,0,n){
		vi curr;
		rep(j,0,m){
			curr.push_back(signs[answer[i]-1][j] - signs[answer[0]-1][j]);
		}
		normalized.push_back(curr);
	}

	rep(i,0,n){
		int minimum = normalized[i][0];
		rep(j,0,m){
			minimum = min(minimum, normalized[i][j]);
		}

		rep(j,0,m){
			normalized[i][j] -= minimum;
			if (normalized[i][j] < 0 || normalized[i][j] > 1) return false;
		}

		
	}
	return true;
}

int main(int argc, char **argv) {
	init_io(argc, argv);
	

	int n, m;
	judge_in >> n >> m;

	vvi signs(n);

	rep(i,0,n){
		rep(j,0,m){
			int temp;
			judge_in >> temp;
			signs[i].push_back(temp);
		}
	}

	auto check = [&](istream& sol, feedback_function feedback)
	{
		int ans;
		if(!(sol >> ans)) feedback("Expected more output");
	
		vi nums;
		rep(i,0,ans){
			int temp;
			if(!(sol >> temp)) feedback("Expected more output (sign indicies)");
			nums.push_back(temp);
		}

		string trailing;
		if(sol >> trailing) feedback("Trailing output");

		if (!valid(nums, signs, ans, m)) feedback("Invalid solution");
		if (!valid_normalized(nums, signs, ans, m)) feedback("Invalid solution");

		return ans;
	};

	int judgeAns = check(judge_ans, judge_error);
	int authorAns = check(author_out, wrong_answer);
	

	// We assume the judge is 100% correct. (which it is)
	if (authorAns>judgeAns) judge_error("Contestant found better solution than judge"); // wrong_answer("Contestant found better solution than judge"); //
	if (authorAns<judgeAns) wrong_answer("Contestant found suboptimal solution");

	accept();
}
