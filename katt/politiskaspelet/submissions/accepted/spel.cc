#include <bits/stdc++.h>  
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  int n; cin >> n;
  vector<int> a; copy_n(istream_iterator<int>(cin), n, back_inserter(a));
  vector<vector<int>> jump(n+1);

  auto getjump = [&](int i, int level) -> int {
    if (i <= 0) return -1;
    int jump_index = level - a[i-1];
    if (jump_index < 0 || jump_index >= (int)jump[i].size())
      return -1;
    return jump[i][jump_index];
  };
  for (int i=0; i<n; ++i) {
    int x = a[i], j;
    jump[i+1].push_back(i);
    while ((j = getjump(jump[i+1].back(), x++)) != -1)
      jump[i+1].push_back(j);
  }

  vector<int> dp(n+1);
  for (int i = 1; i <= n; ++i) {
    int ans = i+1;
    for (int j : jump[i])
      ans = min(ans, dp[j]+1);
    dp[i] = ans;
  }
  cout << dp.back() << '\n';
  return 0;
}
