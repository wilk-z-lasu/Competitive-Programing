#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;

int n,m;
int A,B;
vector<int>vec[maxn];

bool vis[maxn];
int up[maxn];
int depth[maxn];
bool vis_up[maxn];
bool opt=0;
int cykl=0;
void prepere()
{
    for(int i=0;i<n;++i)
    {
        vec[i].clear();
        vis[i]=0;
        up[i]=0;
        depth[i]=0;
        vis_up[i]=0;
    }
    opt=0;
    cykl=0;
}
void mark(int a, int b)
{
    if(opt) return;
    if(a==b) return;
    if(depth[a]<depth[b]) swap(a,b);
    if(vis_up[a]) opt=1;
    vis_up[a]=1;
    a=up[a];
    mark(a,b);
}
void dfs(int v, int ojciec=0)
{
    // cout<<v<<" up: "<<ojciec<<"\n";
    vis[v]=1;
    up[v]=ojciec;
    depth[v]=depth[ojciec]+1;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        if(!vis[u])
            dfs(u,v);
        else if(v<u)
        {
            ++cykl;
            mark(v,u);
        }
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin>>q;
    while(q--)
    {
        cin>>n>>m;
        prepere();
        for(int i=1;i<=m;++i)
        {
            cin>>A>>B;
            vec[A].pb(B);
            vec[B].pb(A);
        }
        for(int i=0;i<n;++i)
            if(!vis[i])
                dfs(i);
        if(opt)
            cout<<"NIE\n";
        else
            cout<<cykl<<"\n";
    }
    return 0;
}