#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;

int n;
int a,b;

vector<int>vec[maxn];
int depth[maxn];
int siz[maxn];
int solv[maxn];

void calculate_depth(int v=1, int parent=0)
{
    siz[v]++;
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        depth[u]=depth[v]+1;
        calculate_depth(u,v);
        siz[v]+=siz[u];
    }
}

void dfs(int v, int parent, int solution)
{
    solv[v]=solution;
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        int up=n-siz[u];
        int down=siz[u]-1;
        dfs(u,v, solution-down+up-1);
    }
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

    calculate_depth();

    int depth_sum=0;
    for(int i=1;i<=n;i++)
        depth_sum+=depth[i];

    dfs(1,0,depth_sum);

    for(int i=1;i<=n;i++)
        cout<<solv[i]<<' ';
    return 0;
}