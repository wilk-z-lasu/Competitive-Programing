#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=107;

int n; int x;
int dp[maxn][maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=i;j++)
        {
            cin>>x;
            dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + x;
        }
    }

    int solv=0;
    for(int i=1;i<=n;i++)
        solv=max(solv, dp[n][i]);
    cout<<solv;
    return 0;
}