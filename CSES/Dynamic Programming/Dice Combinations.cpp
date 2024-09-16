#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e6+7;
constexpr int mod=1e9+7;


int n;
int dp[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=6;i++)
        dp[i]=1;
    for(int i=2; i<=n; i++)
        for(int j=1; j<=6; j++)
            dp[i] = (dp[i]+dp[max(0,i-j)])%mod;
    cout<<dp[n];
    return 0;
}