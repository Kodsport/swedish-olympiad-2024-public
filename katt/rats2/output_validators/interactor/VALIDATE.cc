#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

const int MAX_QUERY = 25000;
int query_count = 0;
int n, k;
set<int> rats;
set<int> target;

vector<vector<int>> g;

int main(int argc, char **argv) {
    init_io(argc, argv);

    judge_in >> n >> k;

    g.resize(n);
    rep(i,0,n-1) {
        int a, b; judge_in >> a >> b;
        a--; b--;
        g[a].pb(b);
        g[b].pb(a);
    }

    rep(i,0,k) {
        int rat;
        judge_in >> rat;
        rat--;
        rats.insert(rat);
    }

    rep(i,0,k) {
        int t;
        judge_in >> t;
        t--;
        target.insert(t);
    }

    // Give initial info
    cout << n << " " << k << endl;
    for (auto r : rats) cout << r + 1 << " ";
    cout << endl;
    for (auto t : target) cout << t + 1 << " ";
    cout << endl;


    // "game loop"
    while (true) {
        string query;
        if (!getline(cin, query)) {
            wrong_answer("expected more queries\n");
        };

        if (query == "activate!") {
            judge_message("activating traps..\n");
            for (auto r : rats) {
                if (target.find(r) == target.end()) wrong_answer("not all rats at target positions\n");
            }
            accept(); // :)
        }

        query_count++;
        if (query_count > MAX_QUERY) wrong_answer("too many queries\n");

        int count;
        set<int> sonar;
        vector<int> input;
        try {
            stringstream ss;
            ss << query;
            ss >> count;
            rep(i,0,count) {
                int x;
                if (!(ss >> x)) wrong_answer("too few sonar devices\n");

                if (i != 0) if (x <= input[i-1]) wrong_answer("sonar devices query not sorted\n");
                if (x < 1 || x > n) {
                    wrong_answer("invalid node index\n");
                }
                sonar.insert(x-1);
                input.pb(x);
            }
        }
        catch (const exception& e) {
            wrong_answer("invalid query\n");
        }
        

        auto getScore = [&]() -> vector<int> {
            // multi source bfs
            vector<int> score(n, -1);
            queue<int> q;

            for (auto x : sonar) {
                q.push(x);
                score[x] = 0;
            }

            while (!q.empty()) {
                int x = q.front(); q.pop();
                for (auto nei : g[x]) {
                    if (score[nei] != -1) continue;
                    score[nei] = score[x] + 1;
                    q.push(nei);
                }
            }

            return score;
        };

        vector<int> score = getScore();

        vector<bool> occupied(n, false);
        for (auto x : rats) occupied[x] = true;

        for (auto x : rats) {
            int best_pos = x;
            int best_score = score[x];

            for (auto nei : g[x]) {
                if (occupied[nei]) continue;
                if (score[nei] > best_score || (score[nei] == best_score && nei < best_pos && best_pos != x)) {
                    best_pos = nei;
                    best_score = score[nei];
                }
            }

            occupied[x] = false;
            occupied[best_pos] = true;
        }

        rats.clear();
        rep(i,0,n) if (occupied[i]) rats.insert(i);
        assert(rats.size()==k);
        for (auto x : rats) cout << x + 1 << " ";
        cout << endl;
    }
}
