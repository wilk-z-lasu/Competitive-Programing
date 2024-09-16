#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxi = 1e6+7;
constexpr int mod = 1e9+7;

int n,x;
int a[107];
int dp[maxi];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>x;

    dp[0]=1;
    for(int i=1; i<=n; i++)
        cin>>a[i];

    for(int j=1;j<=n;j++)
    {
        for(int i=0;i<maxi;i++)
            if(i+a[j]<maxi) dp[i+a[j]] = (dp[i+a[j]] + dp[i])%mod;
    }
    cout<<dp[x];
    return 0;
}