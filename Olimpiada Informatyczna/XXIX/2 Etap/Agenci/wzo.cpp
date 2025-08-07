#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 5e5+7;
constexpr int inf = 1e9+7;

int n,k;
int a,b;

bool taken[maxn];
vector<int> vec[maxn];

int dp[maxn][3];

void dfs(int v=1, int ojciec=-1)
{
    dp[v][0] = dp[v][1] = dp[v][2] = 0;
    for(auto &u: vec[v])
    {
        if(u == ojciec) continue;
        dfs(u, v);
    }

    vector<int>sons;
    for(auto &u: vec[v])
    {
        if(u == ojciec) continue;
        sons.pb(u);
    }

    int base = 0;
    for(auto &u: sons)
        base += dp[u][2];
    if(taken[v])
    {   
        dp[v][0] = base+1;
        dp[v][1] = -inf;
        dp[v][2] = base;

        for(auto &u: sons)
            dp[v][2] = max(dp[v][2], base - dp[u][2] + dp[u][1]);  
    }
    else if(!taken[v])
    {
        dp[v][0] = -inf;
        for(auto &u: sons)
            dp[v][0] = max(dp[v][0], base+1 - dp[u][2] + dp[u][0]);
        
        dp[v][1] = base+1;
        for(auto &u: sons)
            dp[v][1] = max(dp[v][1], base+1 - dp[u][2] + dp[u][1]);
        
        dp[v][2] = base;
        if(sz(sons) >= 2)
        {
            pi up1 = {-inf,0};
            pi up2 = {-inf,0};
            for(auto &u: sons)
            {
                if(dp[u][0]-dp[u][2] >= up1.f)
                {
                    up2 = up1;
                    up1 = {dp[u][0]-dp[u][2], u};
                }
                else if(dp[u][0]-dp[u][2] >= up2.f)
                    up2 = {dp[u][0]-dp[u][2], u};
            }
            pi down1 = {-inf,0};
            pi down2 = {-inf,0};
            for(auto &u: sons)
            {
                if(dp[u][1]-dp[u][2] >= down1.f)
                {
                    down2 = down1;
                    down1 = {dp[u][1]-dp[u][2], u};
                }
                else if(dp[u][1]-dp[u][2] >= down2.f)
                    down2 = {dp[u][1]-dp[u][2], u};
            }

            if(up1.s != down1.s)
                dp[v][2] = max(dp[v][2], base + up1.f + down1.f);
            else
            {
                dp[v][2] = max(dp[v][2], base + up1.f + down2.f);
                dp[v][2] = max(dp[v][2], base + up2.f + down1.f);
            }
        }
    }
    dp[v][2] = max(dp[v][2], dp[v][0]-1);
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=k;++i)
    {
        cin>>a;
        taken[a]=1;
    }
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    dfs();
    cout<<2*(n-k) - dp[1][2]<<'\n';
    return 0;
}