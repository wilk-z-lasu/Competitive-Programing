#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxn = 1e6+7;
constexpr int mod = 1e9+7;

int t;
int n;

int dp[maxn][2];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    dp[1][0]=dp[1][1]=1;
    for(int i=2;i<maxn;i++)
    {
        dp[i][0] = (4*dp[i-1][0] + dp[i-1][1])%mod;
        dp[i][1] = (dp[i-1][0] + 2*dp[i-1][1])%mod;
    }

    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<(dp[n][0]+dp[n][1])%mod<<'\n';
    }
}