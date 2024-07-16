#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;
 
int n,m,k,r;

const int MAXN = 1000001;
const int MAXK = 200001;

vector<vi> grid(MAXN, vi());
int start;

int DX[4] = {0,-1,0,1};
int DY[4] = {1,0,-1,0};
string dir = ">^<v";

vector<vi> C(MAXK, vi());
vector<vi> CW(MAXK, vi());

bool inbounds(int i, int j){
    return i >= 0 && j >= 0 && i < n && j < m;
}

char get_dir(int i, int j){
    rep(c1,0,sz(C[i])){
        if(C[i][c1] == j)return dir[CW[i][c1]];
    }
    return '?';
}

vector<vi> tree(MAXK, vi());
int dist[MAXK] = {0};
int PAR[MAXK] = {0};

int c_from = -1;
int c_to = -1;
bool mark[MAXK] = {0};
int seen = 0;

void dfs1(int i){
    if(mark[i])return;
    mark[i] = 1;
    seen++;
    if(i == start)PAR[i] = -1;
    rep(c1,0,sz(C[i])){
        int j = C[i][c1];
        if(!mark[j]){
            PAR[j] = 1;
            dist[j] = dist[i]+1;
            PAR[j] = i;
            tree[i].push_back(j);
            dfs1(j);
        }
        else{
            if(dist[j] < dist[i] && dist[i]%2 == dist[j]%2){
                // odd cycle
                c_from = j;
                c_to = i;
            }
        }
    }
}

bool fix_parity = 0;
bool done[MAXK] = {0};
string ans = "";

void walk(int i, int j){
    done[j] ^= 1;
    ans += get_dir(i,j);
}

void dfs2(int i){
    if(fix_parity && c_from == i){
        int j = c_to;
        walk(c_from, c_to);
        while(j != i){
            walk(j, PAR[j]);
            j = PAR[j];
        }
        fix_parity = 0;
    }

    trav(y, tree[i]){
        walk(i, y);
        dfs2(y);
    }

    if(!done[i] && i != start){
        walk(i, PAR[i]);
        walk(PAR[i], i);
    }

    if(i != start){
        walk(i, PAR[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    k = 0;
    cin >> n >> m >> r;
    rep(c1,0,n){
        string s;
        cin >> s;
        rep(c2,0,m){
            if(s[c2] != '.'){
                grid[c1].push_back(k);
                if(s[c2] == 'S'){
                    start = k;
                }
                k++;
            }
            else{
                grid[c1].push_back(-1);
            }
        }
    }
    rep(c1,0,n){
        int last = -1;
        rep(c2,0,m){
            int current = grid[c1][c2];
            if(current != -1){
                if(last != -1){
                    C[current].push_back(last);
                    CW[current].push_back(2);
                    C[last].push_back(current);
                    CW[last].push_back(0);
                }
                last = current;
            }
        }
    }
    rep(c2,0,m){
        int last = -1;
        rep(c1,0,n){
            int current = grid[c1][c2];
            if(current != -1){
                if(last != -1){
                    C[current].push_back(last);
                    CW[current].push_back(1);
                    C[last].push_back(current);
                    CW[last].push_back(3);
                }
                last = current;
            }
        }
    }

    dfs1(start);
    if(seen != k){
        // disconnected
        cout << "-1\n";
        return 0;
    }

    if(k%2 == 1 && c_from == -1 && r == 1){
        // bipartite and odd
        cout << "-1\n";
        return 0;
    }

    fix_parity = k%2;
    
    dfs2(start);
    if(!done[start])ans.pop_back();
    cout << sz(ans) << "\n";
    cout << ans << "\n";

    return 0;
}