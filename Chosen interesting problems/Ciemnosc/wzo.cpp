#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;
constexpr int inf=1e9+7;

int n,m;
int a,b;
vector<int> vec[maxn];
vector<pi> graf[maxn];


bool vis[maxn];
int col[maxn];
vector<int> vertexes;

int tab[3];
void dfs(int v, int color=0)
{
    vis[v]=1;
    col[v]=color;
    tab[color]++;
    vertexes.pb(v);

    for(auto &[u, val]: graf[v])
    {
        if(!vis[u])
            dfs(u, (color+val+3)%3);
    }
        
}

int get_odp()
{
    int edges=0;
    for(auto &v: vertexes)
    {
        for(auto &u: vec[v])
        {
            edges++;
            if((col[v]+1)%3 != col[u])
                return (tab[0]+tab[1]+tab[2])*(tab[0]+tab[1]+tab[2]);
        }
    }
    if(tab[0]==0 || tab[1]==0 || tab[2]==0)
        return edges;
    return tab[0]*tab[1]+tab[1]*tab[2]+tab[2]*tab[0];
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);

        graf[a].pb({b, 1});
        graf[b].pb({a, -1});
    }

    int solv=0;
    for(int i=1;i<=n;++i)
    {
        if(!vis[i])
        {
            tab[0]=tab[1]=tab[2]=0;
            vertexes.clear();

            dfs(i);

            solv += get_odp();
        }
    }
    cout << solv << "\n";
    return 0;
}