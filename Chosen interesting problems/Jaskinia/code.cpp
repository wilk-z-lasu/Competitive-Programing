#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>

constexpr int inf=1e9+7;
constexpr int maxn=5e4+7;

int n;
int a,b;
vector<int>vec[maxn];

int solv;

int f[maxn];
map<int,int>S[maxn];
void dfs(int v=1, int ojciec=-1)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
    }
    int m = -1;
    map<int,int>tab;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        for(auto &e: S[u])
            tab[e.f]++;
    }
    for(auto &i: tab)
        if(i.s > 1)
            m = i.f;
    f[v] = m+1;
    while(tab.find(f[v])!=tab.end())
        f[v]++;
    for(auto &u: tab)
        if(u.f>f[v])
            S[v][u.f] = 1;
    S[v][f[v]] = 1;

    solv = max(solv, f[v]);
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
    cout<<solv;
    return 0;
}