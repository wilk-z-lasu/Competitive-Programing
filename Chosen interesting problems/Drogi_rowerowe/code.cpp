#include<bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=50000+7;
constexpr int inf=1e9+7;

int n,m;
int a,b;

vector<int>vec[maxn];
vector<int>vec_odw[maxn];
vector<int>vec_sss[maxn];

int vis[maxn];

stack<int>S;
int sss[maxn];
int sss_size[maxn];
int sss_number;

map<pair<int,int>,bool>i_have;//uwu

inline void DFSstack(int v)
{
    vis[v]=true;
    for(auto &u: vec[v])
    {
        if(!vis[u])
            DFSstack(u);
    }
    S.push(v);
}

void clean_vis()
{
    for(int i=0;i<maxn;i++)
        vis[i]=false;
}

inline void name(int v)
{
    vis[v]=true;
    sss[v]=sss_number;
    for(auto &u: vec_odw[v])
    {
        if(!vis[u])
            name(u);
    }
}

int odp[maxn];

void solv(int v)
{
    odp[v]=sss_size[v];
    vis[v]=true;
    for(auto u: vec_sss[v])
    {
        if(!vis[u])
            solv(u);
        odp[v]+=odp[u];
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec_odw[b].push_back(a);

    }

    clean_vis();
    for(int i=1;i<=n;i++)
        if(!vis[i])
            DFSstack(i);

    clean_vis();
    while(!S.empty())
    {
        if(!vis[S.top()])
        {
            sss_number++;
            name(S.top());
        }
        S.pop();
    }

    for(int i=1;i<=n;i++)
        for(auto &u: vec[i])
            if(sss[i]!=sss[u] && i_have.find({min(sss[i],sss[u]),max(sss[i],sss[u])})==i_have.end())
            {
                vec_sss[sss[i]].push_back(sss[u]);
                i_have[{min(sss[i],sss[u]),max(sss[i],sss[u])}]=1;
            }

    for(int i=1;i<=n;i++)
        sss_size[sss[i]]++;

    clean_vis();
    for(int i=1;i<=sss_number;i++)
        if(!vis[i])
            solv(i);

    for(int i=1;i<=n;i++)
        cout<<odp[sss[i]]-1<<'\n';

    return 0;
}