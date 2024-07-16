#include <bits/stdc++.h>
using namespace std;
#include <cassert>

#define rep(i,n) for (int i = 0; i < n; i++)
#define repp(i,s,n) for (int i = s; i < n; i++)
#define all(x) begin(x),end(x)
typedef long long ll;
typedef vector<ll> vi;

bool issorted(vi nums)
{
    repp(i, 1, nums.size()) if (nums[i] < nums[i-1]) return 0;
    return 1;
}

int main()
{
    int n, x, y;
    cin >> n >> x >> y;

    vi nums(n);
    rep(i, n) cin >> nums[i],nums[i]*=x;
    
    while (!issorted(nums))
    {
        rep(i, n-1)
        {
            if (nums[i] > nums[i + 1]) swap(nums[i], nums[i + 1]);
        }
    }

    
    int t = 0;
    int cnt = 0;
    rep(i, n)
    {
        double newavg = (t + nums[i]) / (cnt + 1);
        if (newavg<=y)
        {
            t += nums[i];
            cnt++;
        }
    }

    cout << cnt;


    return 0;
}