using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back

typedef long long ll;

int n, k;
ll target;
ll current;

void query(ll Q) {
    if (Q == 0) return;
    vector<int> q;
    rep(i,0,n) if (Q&(1<<i)) q.pb(i+1);
    cout << q.size() << " ";
    for (auto x : q) cout << x << " ";
    cout << endl;

    current = 0;
    rep(i,0,k) {
        int x; cin >> x; x--;
        current|=(1<<x);
    }

    if (current == target) {
        cout << "activate!" << endl;
        exit(0);
    }
}

int main() {
    cin >> n >> k;
    int temp;
    rep(i,0,k) cin >> temp; 

    target = 0;
    rep(i,0,k) {
        int x; cin >> x; x--;
        target|=(1<<x);
    }

    while (true) {
        query(rand() % (1<<n));
    }
    return 0;
}