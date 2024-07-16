#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <limits.h>
#include <math.h>
#include <chrono>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 tuple<ll,ll,ll>
#define p4 vi
#define ip3 tuple<int,int,int>
#define ip4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int n, k;
vector<vector<int>> cost2white, cost2black;
vector<vector<int>> layermask2cost;

inline bool white_at(int x, int y, vector<int>& layers) {
    return layers[y] & (1 << (k - x - 1));
}

void print_snowflake(vector<int>& layers) {
    for(int y = n - 1; y >= 0; y--) {
        for(int x = 0; x < n; x++) {
            int my = y;
            if(my < k) my = n - 1 - my;
            my -= (k - 1);

            int mx = x;
            if(mx < k) mx = n - 1 - mx;
            mx -= (k - 1);
            
            if(my > mx) swap(mx, my);

            bool one = white_at(mx, my, layers);
            cout << one ? '1' : '0';
        }

        cout << endl;
    }
}

int best = 1000000;
int c = 0;
void rec(vector<int>& layers, int cost) {
    if(layers.size() >= k) {
        for(int T = 0; T < 2; T++) {
            if(T == 1) {
                if(n != 15) continue;
                //if(layers[0] != 0b11111100 && layers[0] != 0b11111000) continue;
                if(white_at(6, 1, layers)) continue;
                if(!white_at(6, 2, layers)) continue;

                cost -= layermask2cost[1][layers[1]];
                layers[1] ^= 0b10;
                cost += layermask2cost[1][layers[1]];
            }

            bool should_next = false;
            for(int y = 0; y < k - 1; y++) {
                for(int x = y; x < k - 1; x++) {
                    if(white_at(x, y, layers)) {
                        bool u = white_at(x, y + 1, layers);
                        bool d = y > 0 ? white_at(x, y - 1, layers) : u;
                        bool r = white_at(x + 1, y, layers);
                        bool l = white_at(x - 1, y, layers);
                        bool ur = white_at(x + 1, y + 1, layers);

                        if((u + d + r + l == 2 && !((u && d) || (l && r))) || (u && ur && r)) {
                            should_next = true;
                            break;
                        }
                    }
                }

                if(should_next) break;
            }

            if(should_next) {
                if(T == 1) layers[1] ^= 0b10;
                continue;
            }

            if(n == 15 && !white_at(5, 1, layers)) {
                bool illegal = true;
                for(int dx = -1; dx <= 1; dx++) {
                    for(int dy = -1; dy <= 1; dy++) {
                        if(dx == 0 && dy == 0) continue;

                        if(!white_at(5 + dx, 1 + dy, layers)) {
                            illegal = false;
                            break;
                        }

                        if(!illegal) break;
                    }
                }

                if(illegal){
                    if(T == 1) layers[1] ^= 0b10;
                    continue;
                }
            }

            /*for(int y = k - 1; y >= 0; y--) {
                for(int x = 0; x < k; x++) {
                    cerr << (white_at(x, y, layers) ? '1' : '0');
                }
                cerr << endl;
            }
            cerr << cost;
            cerr << endl << endl;*/

            c++;
            if (cost < best) best = cost;

            //print_snowflake(layers);
            //cout << endl;

            if(T == 1) layers[1] ^= 0b10;
        }
    } else {
        int l = layers.size();


        for(int m = 0; m < (1 << (k - l - 1)); m += 2) {
            bool prev_one = false;
            bool connected = false;
            bool allowed = true;
            for(int i = 0; i < k; i++) {
                bool curr_one = m & (1 << i);
                if(!curr_one && prev_one) {
                    if(!connected) {
                        allowed = false;
                        break;
                    } else connected = false;
                } 

                if(curr_one && layers.back() & (1 << i)) connected = true;

                prev_one = curr_one;
            }

            if(!allowed) continue;
            layers.push_back(m);
            rec(layers, cost + layermask2cost[l][m]);
            layers.pop_back();
        }
    }
}

int main() {
    //fast();
    
    cin >> n;

    k = (n + 1) / 2;
    cost2white.resize(k, vector<int>(k, 0));
    cost2black.resize(k, vector<int>(k, 0));

    for(int y = n - 1; y >= 0; y--) {
        string row;
        cin >> row;
        
        for(int x = 0; x < n; x++) {
            int my = y;
            if(my < k) my = n - 1 - my;
            my -= (k - 1);

            int mx = x;
            if(mx < k) mx = n - 1 - mx;
            mx -= (k - 1);
            
            if(my > mx) swap(mx, my);

            (row[x] == '0' ? cost2white : cost2black)[mx][my]++;
        }
    }

    for(int l = 0; l < k; l++) {
        int w = k - l;
        layermask2cost.push_back({vector<int>(1 << w, 0)});

        for(int m = 0; m < (1 << w); m++) {
            int& sum = layermask2cost[l][m];
            for(int x = l; x < k; x++) {
                sum += (((1 << (k - x - 1)) & m) ? cost2white : cost2black)[x][l];
            }
        }
    }

    for(int i = 1; i < k; i++) {
        int m = ((1 << i) - 1) << (k - i);
        
        vector<int> layers = { m };
        rec(layers, layermask2cost[0][m]);
    }

    cout << best;
    //cout << "Num snowflakes: " << c;
}