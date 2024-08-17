#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n;
int a,b;

vector<int>vec[maxn];

int dp[maxn][2];//[0]-without upper edge [1]-with upper edge

void dfs(int v=1, int parent=0)
{
    int maxi=0;
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        dfs(u,v);
        dp[v][1]+=dp[u][0];
        dp[v][0]+=dp[u][0];
        maxi=max(maxi, dp[u][1]-dp[u][0]);
    }
    dp[v][0]+=maxi;
    if(parent!=0)
        dp[v][1]++;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    dfs();
    cout<<max(dp[1][0],dp[1][1]);
    return 0;
}