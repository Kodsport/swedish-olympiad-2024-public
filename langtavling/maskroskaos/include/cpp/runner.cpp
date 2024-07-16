#include <bits/stdc++.h>

#include "maskroskaos.h"

using namespace std;

string SECRET_KEY = "CORRECT HORSE BATTERY STAPLE";

constexpr int MAX_N = 43000;
constexpr int MAX_CALLS = 1000000;

namespace {

void WrongAnswer() {
  cout << "WA";
  exit(0);
}

int n;
int counterpart[2 * MAX_N + 1];

int num_queries;
int num_kinds;
int on[2 * MAX_N + 1];
int cnt[2 * MAX_N + 1];

int num_answers;
int answer[2 * MAX_N + 1];

}  // namespace


int Query(int x) {
  if (!(1 <= x && x <= 2 * n)) {
    WrongAnswer();
  }
  if (++num_queries > MAX_CALLS) {
    WrongAnswer();
  }
  const int type = std::min(x, counterpart[x]);
  if (on[x]) {
    --on[x];
    --cnt[type];
    if (cnt[type] == 0) {
      --num_kinds;
    }
  } else {
    ++on[x];
    ++cnt[type];
    if (cnt[type] == 1) {
      ++num_kinds;
    }
  }
  return num_kinds;
}

void Answer(int a, int b) {
  if (++num_answers > n) {
    WrongAnswer();
  }
  if (!(1 <= a && a <= 2 * n && 1 <= b && b <= 2 * n)) {
    WrongAnswer();
  }
  if (answer[a] != 0) {
    WrongAnswer();
  }
  answer[a] = b;
  if (answer[b] != 0) {
    WrongAnswer();
  }
  answer[b] = a;
  if (!(counterpart[a] == b && counterpart[b] == a)) {
    WrongAnswer();
  }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a,b;
		cin >> a >> b;
		counterpart[a]=b;
		counterpart[b]=a;
	}
	Solve(n);
	if (num_answers != n)
	{
		WrongAnswer();
	}


	cout << SECRET_KEY;
	return 0;
}
