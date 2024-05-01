#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=2e5+7;

int n;
int a,b;

int dp[maxn];
vector<int>vec[maxn];

int solv;

void dfs(int v=1, int ojciec=0)
{
    pair<int,int>maxi={0,0};
    int synowie=0;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
        synowie++;
        if(dp[u]>=maxi.f)
        {
            maxi.s=maxi.f;
            maxi.f=dp[u];
        }
        else if(dp[u]>=maxi.s)
            maxi.s=dp[u];
    }
    if(synowie==0)
        dp[v]=0;
    else if(synowie==1)
    {
        dp[v]=max(maxi.f, 1);
        solv=max(solv, maxi.f+(v!=1));
    }
    else if(synowie>=2)
    {
        dp[v]=max(maxi.f,1)+synowie-1;
        solv=max(solv, maxi.f + (v!=1) + synowie-1);
        solv=max(solv, maxi.f + maxi.s + (v!=1) + synowie-2);
    }
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    dfs();
    cout<<solv;
    return 0;
}