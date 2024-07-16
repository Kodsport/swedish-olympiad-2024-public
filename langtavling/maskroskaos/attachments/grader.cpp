#include <bits/stdc++.h>
#include "maskroskaos.h"

using namespace std;

const int MAX_N = 43000;
const int MAX_QUERIES = 1000000;

// Namespace makes it so that your program can't see these variables
namespace
{

void WrongAnswer(string why) {
  cout << "WA. " << why;
  exit(0);
}

int n;
int counterpart[2 * MAX_N + 1];

int num_queries;
int distinct_cnt;
int in_machine[2 * MAX_N + 1];
int times_in_machine[2 * MAX_N + 1];

int num_answers;
int answer[2 * MAX_N + 1];

}  // namespace


int Query(int x)
{
    if (x < 0 || x > 2 * n) WrongAnswer("Query index out of range");
    if (++num_queries > MAX_QUERIES) WrongAnswer("Too many queries");

    int type = std::min(x, counterpart[x]);
    if (in_machine[x])
    {
        in_machine[x] = false;
        times_in_machine[type]--;
        if (times_in_machine[type] == 0) --distinct_cnt;
    }
    else
    {
        in_machine[x] = true;
        times_in_machine[type]++;
        if (times_in_machine[type] == 1) ++distinct_cnt;
    }
    return distinct_cnt;
}

void Answer(int a, int b)
{
    if (++num_answers > n) WrongAnswer("Answered too many times");
    if (a < 0 || a > 2 * n || b < 0 || b > 2 * n) WrongAnswer("Answer index out of range");
    if (answer[a] != 0) WrongAnswer("Dandelion answered twice");
    answer[a] = b;
    if (answer[b] != 0) WrongAnswer("Dandelion answered twice");
    answer[b] = a;
    if (!(counterpart[a] == b && counterpart[b] == a)) WrongAnswer("Incorrect answer, a and b are not of same kind");
}

int main()
{
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
		WrongAnswer("Did not answer exactly n times");
	}

	cout << "Accepted. Queries: " << num_queries;
	return 0;
}
