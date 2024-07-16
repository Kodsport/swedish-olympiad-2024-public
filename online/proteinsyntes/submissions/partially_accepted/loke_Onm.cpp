#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()

typedef unsigned long long ull;
typedef ull H;
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
    pw[0] = 1;
    rep(i,0,sz(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(int a, int b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

vector<H> getHashes(string& str, int length) {
  if (sz(str) < length) return {};
  H h = 0, pw = 1;
  rep(i,0,length)
    h = h * C + str[i], pw = pw * C;
  vector<H> ret = {h};
  rep(i,length,sz(str)) {
    ret.push_back(h = h * C + str[i] - pw * str[i-length]);
  }
  return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int N; cin >> N;
  string target; cin >> target;
  int M; cin >> M;
  unordered_set<H> uniqueWords;
  vector<string> dictionary(M);
  vector<H> dictHashes(M);
  vector<vi> dictByFirstChar(26);
  rep(i, 0, M) {
    cin >> dictionary[i];
    dictHashes[i] = hashString(dictionary[i]);
    // OPTIMIZATION 1, deduplicated words
    if (uniqueWords.count(dictHashes[i]) == 0) {
      uniqueWords.insert(dictHashes[i]);
      dictByFirstChar[dictionary[i][0]-'a'].push_back(i);
    }
  }
  HashInterval targetHash(target);
  vi countToBuild(N+1, 1e9);
  countToBuild[0] = 0;
  rep(i, 0, N) {
    // OPTIMIZATION 2, only loop over words with correct first letter
    for(int j : dictByFirstChar[target[i]-'a']) {
      int len = sz(dictionary[j]);
      if (i+len <= N && dictHashes[j] == targetHash.hashInterval(i, i+len)) {
        countToBuild[i+len] = min(countToBuild[i+len], 1+countToBuild[i]);
      }
    }
  }
  cout << countToBuild[N] << endl;
}
