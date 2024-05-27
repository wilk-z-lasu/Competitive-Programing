#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 
#define ll long long
constexpr int maxn=100000+7;
constexpr int maxm=500000+7;

int n,m;
int a,b;
pair<int,int>tab[maxm];
vector<int>vec[maxn];

int depth[maxn];
int low[maxn];
bool vis[maxn];
bool taken[maxm];
int w[maxn];
ll odp[maxn];

void dfs(int v)
{
    vis[v]=1;
    low[v]=depth[v];
    for(auto &it: vec[v])
    {
        if(!taken[it])
        {
            taken[it]=1;
            int u;
            if(tab[it].f==v)
                u=tab[it].s;
            else
                u=tab[it].f;

            if(!vis[u])
            {
                depth[u]=depth[v]+1;
                dfs(u);
                w[v]+=w[u];
            }
            low[v]=min(low[v],low[u]);
        }
    }
    w[v]++;
}

void solv(int v)
{
    vis[v]=1;
    ll grupa_up=n-w[v];
    for(auto &it: vec[v])
    {
        if(!taken[it])
        {
            taken[it]=1;
            int u;
            if(tab[it].f==v)
                u=tab[it].s;
            else
                u=tab[it].f;
            
            if(!vis[u])
            {
                //krawedz do syna
                if(low[u]<depth[v])//syn ma polaczenie do grupy_up
                    grupa_up+=w[u];
                else
                    odp[v]+=(ll)w[u]*(n-1-w[u]);
                solv(u);
            }
            //krawedz zwrotna <- nie potrzebna
        }
    }
    odp[v]+=grupa_up*(n-1-grupa_up);
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
        tab[i]={a,b};
        vec[a].push_back(i);
        vec[b].push_back(i);
    }
    depth[1]=1;
    dfs(1);

    // clear
    for(int i=0;i<maxn;i++)
        vis[i]=0;
    for(int i=0;i<maxm;i++)
        taken[i]=0;
    solv(1);

    for(int i=1;i<=n;i++)
        cout<<odp[i]+(n-1)*2<<'\n';
    return 0;
}