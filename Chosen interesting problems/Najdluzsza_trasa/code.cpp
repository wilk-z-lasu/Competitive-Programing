#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=200000+7;

int n;
int c[maxn];
int a,b;
vector<int>vec[maxn];

pair<int,int>k;
int solv;

void dfs(int v=1, int ojciec=0, int depth=0)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v,depth+1);
    }
    k=max(k,{depth,v});
}
void dfs2(int start, int v, int ojciec=0, int depth=0)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs2(start,u,v,depth+1);
    }
    if(c[v]!=c[start])
        solv=max(solv,depth);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>c[i];

    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    dfs();
    int v1=k.s;

    k={0,0};
    dfs(v1);
    int v2=k.s;

    dfs2(v1, v1);
    dfs2(v2, v2);

    cout<<solv;
    return 0;
}