#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=507;
constexpr int inf=1e9+7;


int a,b;
int dp[maxn][maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for(int i=1; i<maxn; i++)
        for(int j=1; j<maxn; j++)
            dp[i][j]=inf;

    for(int i=1; i<maxn; i++)
        dp[i][i]=0;

    for(int i=1; i<maxn; i++)
    {
        for(int j=1; j<maxn; j++)
        {
            for(int cut=1; cut<=i-1; cut++)
                dp[i][j] = min(dp[i][j], dp[cut][j]+dp[i-cut][j]+1);
            for(int cut=1; cut<=j-1; cut++)
                dp[i][j] = min(dp[i][j], dp[i][cut]+dp[i][j-cut]+1);
        }
    }

    cin>>a>>b;
    cout<<dp[a][b];
    return 0;
}