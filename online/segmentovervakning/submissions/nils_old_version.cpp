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

map<int,int> LM,RM;
vector<set<pii>> LS,RS;

map<int,int> serial_to_id;
vi L,R;

set<pii> lefts, mrights;

void add(int serial, int lo, int hi){
    serial_to_id[serial] = sz(L);
    L.push_back(lo);
    R.push_back(hi);
    lefts.insert({lo, serial});
    mrights.insert({-hi, serial});

    if(LM.find(lo) == LM.end()){
        LM[lo] = sz(LS);
        set<pii> temp;
        LS.push_back(temp);
    }
    if(RM.find(hi) == RM.end()){
        RM[hi] = sz(RS);
        set<pii> temp;
        RS.push_back(temp);
    }

    LS[LM[lo]].insert({-hi, serial});
    RS[RM[hi]].insert({lo, serial});
}

void rm(int serial){
    int i = serial_to_id[serial];
    int lo = L[i];
    int hi = R[i];
    LS[LM[lo]].erase({-hi, serial});
    RS[RM[hi]].erase({lo, serial});
    lefts.erase({lo, serial});
    mrights.erase({-hi, serial});
}

void answer(){
    assert(sz(lefts) > 0);
    int mi = (*lefts.begin()).first;
    int ma = -(*mrights.begin()).first;

    int hi = -(*LS[LM[mi]].begin()).first;
    int lo = (*RS[RM[ma]].begin()).first;

    if(hi == ma){
        cout << "1\n";
    }
    else{
        if(hi >= lo){
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