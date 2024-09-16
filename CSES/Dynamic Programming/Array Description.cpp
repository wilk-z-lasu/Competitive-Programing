#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxn = 1e5+7;
constexpr int maxm = 1e2+7;
constexpr int mod = 1e9+7;

int n, m;
int x[maxn];

int dp[maxn][maxm];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>x[i];

    x[n+1]=1;

    int start=1;
    while(x[start]==0)
        start++; 

    if(start == n+1)
    {
        for(int i=1;i<=m;i++)
            dp[1][i]=1;

        for(int i=2;i<=n;i++)
            for(int j=1;j<=m;j++)
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1])%mod;
        int solv=0;
        for(int i=1;i<=m;i++)
            solv=(solv+dp[n][i])%mod;
        cout<<solv;
        return 0;
    }

    dp[start][x[start]]=1;
    for(int i=start+1;i<=n;i++)
    {
        if(x[i] == 0)
            for(int j=1;j<=m;j++)
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1])%mod;
        else
            dp[i][x[i]] = (dp[i-1][x[i]-1] + dp[i-1][x[i]] + dp[i-1][x[i]+1])%mod;
    }

    int solv1=0;
    for(int j=1;j<=m;j++)
        solv1 = (solv1 + dp[n][j])%mod;

    for(int i=start-1;i>=1;i--)
    {
        if(x[i] == 0)
            for(int j=1;j<=m;j++)
                dp[i][j] = (dp[i+1][j-1] + dp[i+1][j] + dp[i+1][j+1])%mod;
        else
            dp[i][x[i]] = (dp[i+1][x[i]-1] + dp[i+1][x[i]] + dp[i+1][x[i]+1])%mod;
    }

    int solv2=0;
    for(int j=1;j<=m;j++)
        solv2 = (solv2 + dp[1][j])%mod;
    cout<<(solv1 * solv2)%mod;
}