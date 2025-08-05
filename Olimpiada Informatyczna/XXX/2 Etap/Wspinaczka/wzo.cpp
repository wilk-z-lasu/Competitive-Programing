#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 1e5+7;

int n,m,k;
int val[maxn];
int a,b;
int vec[maxn];
int dp[maxn][1<<8];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;

    for(int i=1;i<=n;++i)
        cin>>val[i];
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec[a] |= (1 << (b-a));
    }

    dp[n][1]=val[n];
    for(int i=n-1;i>=1;--i)
    {
        for(int mask = 0; mask < (1 << k); ++mask)
        {
            if(mask & 1)
                dp[i][mask] = dp[i+1][(mask | vec[i])>>1] + val[i];
            else
                dp[i][mask] = dp[i+1][mask>>1];
        }
    }
    for(int i=1;i<=n;++i)
        cout<<dp[i][1]<<'\n';
    return 0;
}