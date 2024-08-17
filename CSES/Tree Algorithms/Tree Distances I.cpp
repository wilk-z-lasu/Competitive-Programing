#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=2e5+7;

int n;
int a,b;

vector<int>vec[maxn];

int solv[maxn];

pair<int,int> dfs(int v=1, int parent=0, int depth=0)
{
    pair<int,int>odp={depth, v};
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        odp=max(odp, dfs(u,v, depth+1));
    }
    return odp;
}

void mark(int v, int parent=0, int depth=0)
{
    solv[v]=max(solv[v],depth);
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        mark(u,v, depth+1);
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

    pair<int,int> v1=dfs();
    pair<int,int> v2=dfs(v1.s);

    mark(v1.s);
    mark(v2.s);

    for(int i=1;i<=n;i++)
        cout<<solv[i]<<' ';
    return 0;
}