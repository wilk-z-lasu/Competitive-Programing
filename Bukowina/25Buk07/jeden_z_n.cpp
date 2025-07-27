//IT IS NOT A FULL SOLUTION, IT GETS 36 POINTS
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

int mod = 1;
constexpr int maxn = 1e5+7;

int n,m;
int a[maxn];
int b[maxn];
int dp[maxn][2];

int silnia[maxn];

inline int pot(int x, int k) {
    int odp=1;
    while (k)
    {
        if(k&1)
            odp = (odp*x)%mod;
        x = (x*x)%mod;
        k>>=1;
    }
    return odp;
}

inline int symbol_newtona(int x, int k)
{
    if(k>x)
        return 0;
    if(k<=0) 
        return 1;
    return (silnia[x] * pot((silnia[k]*silnia[x-k])%mod, mod-2))%mod;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    if(n>0)
        mod = 998244353;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1;i<=n;++i)
        cin>>b[i];

    silnia[0]=1;
    for(int i=1;i<=m;++i)
        silnia[i] = (silnia[i-1]*i)%mod;

    for(int j=1;j<=n;++j)
    {
        for(int z=0;z<=m;++z)
            dp[z][0]=dp[z][1]=0;
        dp[0][0]=dp[0][1]=1;
        for(int i=1;i<=n;++i)
        {
            for(int z=0;z<=m;++z)
                dp[z][i&1] = dp[z][(i-1)&1];
            if(i==j)
            {
                continue;
            }
            for(int used=1;used<=b[i]-1;++used)
                for(int z=used;z<=m;++z)
                {
                    if(dp[z-used][(i-1)&1] == 0) break;
                    dp[z][i&1] = (dp[z][i&1] + (dp[z-used][(i-1)&1]*symbol_newtona(a[i], used))%mod)%mod;
                }
        }
        int odp = 0;

        for(int i=b[j];i<=m && dp[i-b[j]][n%2]>0;++i)
            odp = (odp + ((((((symbol_newtona(a[j],b[j])*b[j])%mod*dp[i-b[j]][n%2])%mod)*silnia[i-1])%mod)*silnia[m-i])%mod)%mod;
        cout<<odp<<' ';
    }
}