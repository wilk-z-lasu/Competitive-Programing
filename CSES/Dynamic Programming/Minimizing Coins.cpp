#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxi = 1e6+7;
constexpr int inf = 1e9+7;

int n,x;
int a;
int dp[maxi];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>x;

    dp[0]=0;
    for(int i=1;i<maxi;i++)
        dp[i]=inf;

    for(int i=1; i<=n; i++)
    {
        cin>>a;
        for(int j=a;j<maxi;j++)
            dp[j]=min(dp[j], dp[j-a]+1);
    }
    if(dp[x]==inf)
        cout<<-1;
    else
        cout<<dp[x];
    return 0;
}