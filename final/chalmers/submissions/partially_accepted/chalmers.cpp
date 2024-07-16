#ifdef LOCAL
    #pragma GCC optimize("Ofast,unroll-loops") // O3 for geo
    #pragma GCC target("avx2,sse4.2,lzcnt,popcnt,bmi,bmi2")
#endif

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<ll> vll;

const int MOD = 1e9 + 7; // 998244353; 
const int maxN = 1e5 + 5;

#define fuck(x) cout << #x << " " << x << "\n"

#define ff first
#define ss second

void setIO() {
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
}

// void fin() {
//     freopen("a.in", "r", stdin);
//     freopen("a.out", "w", stdout);
// }

int cur = 1;
pii chi[20], sib[20];
int par[20];
string s;
vector<string> path[20];

vi low;

void search1(int at, int dep, int gd = 4) {
    string cpy = s;
    // cerr << at << " " << path[at].size() << endl;
    if(dep == gd) {
        low.push_back(at); 
        if(cpy[0] == '1') cout << "up" << endl, cin >> s;
        return;
    }

    if(cpy[3] == '1') chi[at].ff = ++cur, par[cur] = at;
    if(cpy[2] == '1') chi[at].ss = ++cur, par[cur] = at;

    if(cpy[2] == '1' && cpy[3] == '1') {
        sib[chi[at].ff].ss = chi[at].ss;
        sib[chi[at].ss].ff = chi[at].ff;
        // cerr << chi[at].ff << " and " << chi[at].ss << " are siblings" << endl;
    }

    if(cpy[3] == '1') {
        // see if left has adj
        if(sib[at].ff > 0 && chi[sib[at].ff].ss > 0) {
            sib[chi[at].ff].ff = chi[sib[at].ff].ss;
            sib[chi[sib[at].ff].ss].ss = chi[at].ff;
            // cerr << chi[sib[at].ff].ss << " and " << chi[at].ff << " are siblings" << endl;
        }
        path[chi[at].ff].insert(path[chi[at].ff].end(), path[at].begin(), path[at].end());
        path[chi[at].ff].push_back("downleft");
        cout << "downleft" << endl;
        cin >> s;
        search1(chi[at].ff, dep + 1, gd);
    }

    if(cpy[2] == '1') {
        // see if right has adj
        if(sib[at].ss > 0 && chi[sib[at].ss].ff > 0) {
            sib[chi[at].ss].ss = chi[sib[at].ss].ff;
            sib[chi[sib[at].ss].ff].ff = chi[at].ss;            
            // cerr << chi[at].ss << " and " << chi[sib[at].ss].ff<< " are siblings" << endl;
        }
        path[chi[at].ss].insert(path[chi[at].ss].end(), path[at].begin(), path[at].end());
        path[chi[at].ss].push_back("downright");
        cout << "downright" << endl;
        cin >> s;
        search1(chi[at].ss, dep + 1, gd);
    }


    if(cpy[0] == '1') cout << "up" << endl, cin >> s;
}

int ans[20];
void dfs(int at) {
     // if can travel left and right do that first
    if(sib[at].ff > 0 && ans[sib[at].ff] == -1) ans[sib[at].ff] = ans[at] + 1, dfs(sib[at].ff);
    if(sib[at].ss > 0 && ans[sib[at].ss] == -1) ans[sib[at].ss] = ans[at] + 1, dfs(sib[at].ss);
    
    // travel down
    if(chi[at].ff > 0 && ans[chi[at].ff] == -1) ans[chi[at].ff] = ans[at] + 1, dfs(chi[at].ff);
    if(chi[at].ss > 0 && ans[chi[at].ss] == -1) ans[chi[at].ss] = ans[at] + 1, dfs(chi[at].ss);

    // travel up
    if(par[at] > 0 && ans[par[at]] == -1) ans[par[at]] = ans[at] + 1, dfs(par[at]);
}

vi searchdists(int st) {
    for(int i = 0; i < 20; i++)
        ans[i] = -1;
    
    ans[st] = 0;
    dfs(st);

    vi ret(low.size(), -1);
    for(int i = 0; i < low.size(); i++)
        ret[i] = ans[low[i]];
    return ret;
}

int dist = 2000;
void moveto(int cur, int goal) {
    if(cur == 1) {
        for(auto v : path[goal]) {
            cout << v << endl;
            cin >> s;
        }
    } else {
        while(cur != goal) {
            cout << "up" << endl;
            cin >> s;
            cur = par[cur];
        }
    }
}

pii doasearch(int sta, int stb) {
    pii ret = {-1, -1};
    moveto(1, sta);
    cout << "app" << endl;
    cin >> ret.ff;
    moveto(sta, 1);
    moveto(1, stb);
    cout << "app" << endl;
    cin >> ret.ss;
    moveto(stb, 1);
    return ret;
}

void resetall() {
    for(int i = 0; i < 20; i++)
        chi[i] = sib[i] = {-1, -1}, par[i] = -1, path[i].clear();
    cur = 1;
    low.clear();
}

void searchnexttwo() {
    resetall();
    string tmp;
    if(dist == 1) {
        if(s[3] == '1') {
            cout << "downleft" << endl;
            cin >> tmp;
            cout << "app" << endl;
            int val;
            cin >> val;
            if(val != 0) cout << "right" << endl, cin >> s;
            dist = 0;
            return;
        }
        if(s[2] == '1') {
            cout << "downright" << endl;
            cin >> tmp;
            dist = 0;
            return;
        }
    }

    if (s[3] == '1') {
        cout << "downleft" << endl;
        cin >> tmp;
        if(tmp[2] == '0' && s[2] == '1') {
            cout << "right" << endl;
            cin >> tmp;
            if(tmp[3] == '1') {
                cout << "downleft" << endl;
                cin >> s;
                cout << "app" << endl;
                int val;
                cin >> val;
                if(val == dist - 1) {
                    cout << "right" << endl;
                    cin >> s;
                    dist -= 2;
                    return;
                } else if(val == dist + 1) {
                    cout << "up" << endl;
                    cin >> tmp;
                    cout << "left" << endl;
                    cin >> tmp;
                    cout << "downleft" << endl;
                    cin >> s;
                    dist -= 2;
                    return;
                } else {
                    dist -= 2;
                    return;
                }
            } else if (tmp[2] == '1') {
                cout << "downright" << endl;
                cin >> s;
                cout << "app" << endl;
                int val;
                cin >> val;
                if(val == dist - 2) {
                    dist -= 2;
                    return;
                } else {
                    cout << "up" << endl;
                    cin >> tmp;
                    cout << "left" << endl;
                    cin >> tmp;
                    cout << "downleft" << endl;
                    cin >> s;
                    dist -= 2;
                    return;
                }
            } else {
                cout << "left" << endl;
                cin >> tmp;
                cout << "downleft" << endl;
                cin >> s;
                dist -= 2;
                return;
            }
        } else {
            // just use downleft
            cout << "downleft" << endl;
            cin >> tmp;
            cout << "app" << endl;
            int val;
            cin >> val;
            for(int i = val; i > dist - 2; i--)
                cout << "right" << endl, cin >> s;
            dist -= 2;
            return;
        }
    } else if(s[2] == '1') {
        cout << "downright" << endl;
        cin >> tmp;
        if(tmp[3] == '1') {
            cout << "downleft" << endl;
            cin >> tmp;
            cout << "app" << endl;
            int val;
            cin >> val;
            if(val == dist - 1) cout << "right" << endl, cin >> s;
            dist -= 2;
            return;
        } else {
            cout << "downright" << endl;
            cin >> s;
            dist -= 2;
            return;
        }
    }
}

bool found = 0;
void tryeverything(int at = 1, int cd = 1, int md = 6) {
    cout << "app" << endl;
    int val;
    cin >> val;
    if(val == 0) {
        cout << "here" << endl;
        found = 1;
        return;
    }
    string cpy = s;
    if(cpy[3] == '1' && cd + 1 <= md) {
        cout << "downleft" << endl;
        cin >> s;
        tryeverything(cur, cd + 1);
    }

    if(found) return;

    if(cpy[2] == '1' && cd + 1 <= md) {
        cout << "downright" << endl;
        cin >> s;
        tryeverything(cur, cd + 1);
    }

    if(found) return;
    if(cpy[0] == '1') cout << "up" << endl, cin >> s;
}

void fullsearchok(int md = 6) {
    while(s[0] == '1') {
        cout << "up" << endl;
        cin >> s;
    }
    tryeverything();
}

int main() {
	setIO();

    // "up", "right", "downright", "downleft", or "left"
    cin >> s;
    while(s[0] == '1') {
        cout << "up" << endl;
        cin >> s;
    }

    int at = 1;
    resetall();
    search1(at, 1);

    cerr << "DONESEARCH" << endl;

    if(low.empty()) {
        // cerr << "trying everything" << endl;
        tryeverything();
        return 0;
    }

    // for(auto v : low)
    //     cerr << v << " ";
    // cerr << endl;

    bool fnd = 0;
    for(int i = 0; i < low.size(); i++) {
        vi kys1 = searchdists(low[i]);
        for(int j = i + 1; j < low.size(); j++) {
            vi kys2 = searchdists(low[j]);

            // if each value in ky1 - ky2 is distinct
            set<int> KYSS;
            for(int p = 0; p < kys1.size(); p++)
                KYSS.insert(kys1[p] - kys2[p]);

            if(KYSS.size() == low.size()) {
                for(int p = 0; p < kys1.size(); p++)
                    cerr << kys1[p] - kys2[p] << " ";
                cerr << "\n";
                pii okk = doasearch(low[i], low[j]);
                for(int p = 0; p < kys1.size(); p++) {
                    if(okk.ff - okk.ss == kys1[p] - kys2[p]) {
                        moveto(at, low[p]);
                        vi notsure = searchdists(low[p]);
                        dist = okk.ff - notsure[i];
                        at = low[p];
                        fnd = 1;
                        break;
                    }
                }
            }
            if(fnd) break;
        }
        if(fnd) break;
    }

    assert(dist != 2000);
    cerr << "dist: " << dist << endl;

    if(dist <= 3) {
        fullsearchok();
        return 0;
    }
    while(dist) {
        searchnexttwo();
    }

    cout << "here" << endl;

    return 0;
}