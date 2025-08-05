#include <bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e6+7;
constexpr int maxA = 5e6+7;

int n,a,sum;
vector<int>vec;
int last = 0;

int available[maxA];
bitset<maxA> dp;

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a;
        vec.pb(a);
    }
    sort(vec.begin(), vec.end());
    last = vec.back();
    vec.pop_back();

    for(auto &u: vec)
    {
        sum += u;
        ++available[u];
    }

    dp[0] = 1;
    for(int i=1;i<maxA;++i)
    {
        --available[i];
        if(available[i] >= 2)
            available[2*i] += available[i] / 2;
        available[i] %= 2;
        ++available[i];
        while(available[i]--)
            dp |= (dp << i);
    }
    for(int i=sum/2; i>=0; --i)
    {
        if(dp[i])
        {
            cout << i + last;
            return 0;
        }
    }
}