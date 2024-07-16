#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


void run() {
  int maxn = Arg("maxn");
  int t = Int(1,2); Endl();

  if (t == 1) {
    int c = Int(1, 25); Space(); int n = Int(1, maxn);
    Endl();
    vector<vector<bool>> Room(c);
    rep(i,0,c) Room[i].resize(1<<i);
    rep(i,0,c) {
      rep(j,0,1<<i) {
        int x = Int(0, 1);
        Room[i][j] = (x==1);
        if (j != (1<<i)-1) Space();
      }
      Endl();
    }
    assert(Room[0][0]);

    int A = Int(1, n);
    Endl();
    vector<int> pathA(A);
    rep(i,0,A) {
      pathA[i] = Int(0,1); 
      if (i != A-1) Space();
    }
    Endl();
    int B = Int(1, n);
    Endl();
    vector<int> pathB(B);
    rep(i,0,B) {
      pathB[i] = Int(0,1); 
      if (i != B-1) Space();
    }
    Endl();

    auto validate_path = [&](vector<int> & path) {
      int level = 0, offset = 0;
      rep(i,0,path.size()) {
        if (level == c - 1) {
          assert(path[i] == 0);
          level = 0; offset = 0;
        }
        else {
          level++; offset = offset * 2 + path[i];
          assert(Room[level][offset]);
        }
      }
    };

    validate_path(pathA);
    validate_path(pathB);
  }

  if (t == 2) {
    int n = Int(1, maxn);
    Endl();
    int A = Int(1, n);
    Endl();
    for (int i = 0; i < A; i++) {
      int bit = Int(0,1);
      if (i < A-1) Space();
    }
    Endl();
    int B = Int(n-1,n-1);
    Endl();
    for (int i = 0; i < B; i++) {
      int bit = Int(0,0);
      if (i < B - 1) Space();
    }
    Endl();
  }

  Eof();
}

