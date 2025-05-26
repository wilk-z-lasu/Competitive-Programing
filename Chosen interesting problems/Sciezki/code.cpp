#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)(A.size())

constexpr int maxn=3e5+7;
int n,m,k;
int color[maxn];
int a,b;
vector<int>vec[maxn];

int dp[1<<5][maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>k;
    for(int i=1;i<=n;++i)
    {
        cin>>color[i];
        color[i]--;
    }
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    for(int i=1;i<=n;++i)
        dp[(1<<color[i])][i]=1;

    for(int mask=1;mask<(1<<k);++mask)
        for(int i=1;i<=n;++i)
            for(auto &u: vec[i])
                if(!(mask & (1<<color[u])))
                    dp[mask | (1<<color[u])][u] += dp[mask][i];

    int solv=0;
    for(int mask=1;mask<(1<<k);++mask)
    {
        if(__builtin_popcount(mask)==1) continue;
        for(int i=1;i<=n;++i)
            solv += dp[mask][i];
    }
    cout<<solv;
    return 0;
}