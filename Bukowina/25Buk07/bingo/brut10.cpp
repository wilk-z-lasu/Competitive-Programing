#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 20+1;

int n,p;
int dp[maxn][(1<<maxn)][2][2];
bool d1[maxn][maxn];
bool d2[maxn][maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>p;
    for(int i=1;i<=n;++i)
    {
        d1[i][i]=1;
        d2[i][n+1-i]=1;
    }

    if(n==1)
    {
        cout<<(1%p);
        return 0;
    }
    if(n==2)
    {
        cout<<(4%p);
        return 0;
    }

    dp[0][0][0][0]=1;
    for(int i = 0; i < n; ++i)
    {
        for(int p1 = 0; p1 <= 1; ++p1)
        {
            for(int p2 = 0; p2 <= 1; ++p2)
            {
                for(int mask = 0; mask < (1<<n); ++mask)
                {
                    for(int add = 0; add < n; ++add)
                    {
                        if(mask & (1<<add)) continue;
                        dp[i+1][mask | (1<<add)][p1 | d1[i+1][add+1]][p2 | d2[i+1][add+1]] += dp[i][mask][p1][p2];
                        dp[i+1][mask | (1<<add)][p1 | d1[i+1][add+1]][p2 | d2[i+1][add+1]] %= p;
                    }
                }
            }
        }
    }
    cout<<dp[n][(1<<n)-1][1][1];
}