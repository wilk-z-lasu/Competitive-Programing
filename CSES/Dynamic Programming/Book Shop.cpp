#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn = 1e3+7;
constexpr int maxi = 1e5+7;
constexpr int inf = 1e9+7;

int n,x;
int price[maxn];
int pages[maxn];

int dp[maxi];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>x;
    for(int i=1;i<=n;i++)
        cin>>price[i];
    for(int i=1;i<=n;i++)
        cin>>pages[i];

    dp[0]=0;
    for(int i=1;i<maxi;i++)
        dp[i]=-inf;

    for(int j=1;j<=n;j++)
    {
        for(int i=maxi;i>=price[j];i--)
            if(dp[i-price[j]] != -inf)dp[i]=max(dp[i], dp[i-price[j]] + pages[j]);
    }

    int solv=0;
    for(int i=0;i<=x;i++)
        solv=max(solv,dp[i]);
    cout<<solv;
    return 0;
}