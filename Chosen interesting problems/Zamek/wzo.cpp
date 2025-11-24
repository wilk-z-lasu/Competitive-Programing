#include <iostream>
#include <algorithm>
#include <vector>

#define int long long 
 
using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

const int maxn=2e5+7;
int n, m, q;
int a,b,c;
vector<pair<int,pi>>edges;

vector<pi>vec[maxn];

int rep[maxn];
int siz[maxn];
//find&union
int Find(int x)
{
    if(rep[x]==x) return x;
    return rep[x]=Find(rep[x]);
}
void Union(int a,int b)
{
	a=Find(a);
	b=Find(b);
    rep[a]=rep[b];
    siz[b]+=siz[a];
}
void prepere()
{
    for(int i=1;i<maxn;++i)
    {
        rep[i]=i;
        siz[i]=1;
    }
}

const int LOG = 18;
int up[maxn][LOG][2];
int depth[maxn];

void dfs(int v=1, int parent=1, int cost=0)
{
    up[v][0][0]=parent;
    up[v][0][1]=cost;

    for(auto &z: vec[v])
    {
        int u = z.f;
        int c = z.s;
        if(u==parent) continue;
        depth[u]=depth[v]+1;
        dfs(u, v, c);
    }
}

void calculate_bin_lifting()
{
    for(int jump=1;jump<LOG;++jump)
        for(int i=1;i<=n;i++)
        {
            up[i][jump][0] = up[up[i][jump-1][0]][jump-1][0];
            up[i][jump][1] = max(up[i][jump-1][1], up[up[i][jump-1][0]][jump-1][1]);
        }
}

int get_max(int a, int b)
{
    int odp = 0;
    if(depth[a] < depth[b]) swap(a,b);//depth[a]>=depth[b]

    int k=depth[a]-depth[b];

    for(int i=LOG-1;i>=0;i--)
        if(k & (1<<i))
        {
            odp=max(odp, up[a][i][1]);
            a=up[a][i][0];
        }
    if(a==b) return odp;
    
    for(int i=LOG-1;i>=0;i--)
        if(up[a][i][0] != up[b][i][0])
        {
            odp = max(odp, up[a][i][1]);
            odp = max(odp, up[b][i][1]);

            a=up[a][i][0];
            b=up[b][i][0];
        }
    odp = max(odp, up[a][0][1]);
    odp = max(odp, up[b][0][1]);
    return odp;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b>>c;
        edges.pb({c,{a,b}});
    }
    sort(edges.begin(), edges.end());

    int odp=0;
    prepere();
    for(auto &e: edges)
    {
        int x=e.s.f;
        int y=e.s.s;
        int w=e.f;
        if(Find(x)!=Find(y))
        {
            vec[x].pb({y,w});
            vec[y].pb({x,w});
            Union(x,y);
            odp+=w;
        }
    }

    dfs();
    calculate_bin_lifting();

    cin>>q;
    for(int i=1;i<=q;++i)
    {
        cin>>a>>b;
        if(Find(a)==Find(b) && siz[Find(a)]==n)
            cout<<odp-get_max(a,b)<<'\n';
        else if(Find(a)!=Find(b) && siz[Find(a)]+siz[Find(b)]==n)
            cout<<odp<<'\n';
        else
            cout<<"Ojojoj\n";
    }
}