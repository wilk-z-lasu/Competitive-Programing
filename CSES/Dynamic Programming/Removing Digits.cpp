#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn = 1e6+7;
constexpr int inf = 1e9+7;

int n;
int dp[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    dp[0]=0;
    for(int i=1;i<maxn;i++)
        dp[i]=inf;
    for(int i=1; i<=n; i++)
    {
        int v=i;
        while(v)
        {
            dp[i]=min(dp[i], dp[i-v%10]+1);
            v/=10;
        }
    }

    cout<<dp[n];
    return 0;
}