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

const int MAXN = 300001;
const int inf = 1e9;

int q;

map<int,int> serial_to_id;
vi L,R;
set<pii> lefts, mrights;
int xmin, xmax;

void add(int serial, int lo, int hi){
    serial_to_id[serial] = sz(L);
    L.push_back(lo);
    R.push_back(hi);
    if(hi >= xmax)lefts.insert({lo, 0});
    if(lo <= xmin)mrights.insert({-hi, 0});
}

void rm(int serial){
    int i = serial_to_id[serial];
    int lo = L[i];
    int hi = R[i];
    if(hi >= xmax)lefts.erase({lo, 0});
    if(lo <= xmin)mrights.erase({-hi, 0});
}

void answer(){
    int mi = -1e9;
    int ma = 2e9;
    if(sz(lefts) > 0)ma = (*lefts.begin()).first;
    if(sz(mrights) > 0)mi = -(*mrights.begin()).first;
    if(mi >= xmax || ma <= xmin){
        cout << "1\n";
    }
    else{
        if(mi >= ma){
            cout << "2\n";
        }
        else{
            cout << "-1\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> xmin >> xmax;
    cin >> q;
    
    rep(c1,0,q){
        char typ;
        int serial, lo, hi;
        cin >> typ >> serial;
        if(typ == '+'){
            cin >> lo >> hi;
            add(serial, lo, hi);
        }
        else{
            rm(serial);
        }
        answer();
    }

    return 0;
}