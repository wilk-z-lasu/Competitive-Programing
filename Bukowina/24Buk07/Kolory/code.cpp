#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=100000+7;
constexpr int inf=1e9+7;

constexpr int LOG=20;


int n,q;
int a,b;
int c;
char zap;

vector<int>vec_input[maxn];

int depth[maxn];
int up[maxn][LOG];

int color_v[maxn];
set<int>color_wierzcholki[maxn];
int color_odp[maxn];

int numeruj;
int numer[maxn];
void renumer(int v=1, int dep=1, int parent=1)
{
    numeruj++;
    numer[v]=numeruj;
    up[numer[v]][0]=numer[parent];
    depth[numer[v]]=dep;

    for(auto &u: vec_input[v])
    {
        if(u==parent) continue;
        renumer(u,dep+1,v);
    }
}

void calculate_bin_lifting()
{
    for(int jump=1;jump<LOG;jump++)
        for(int i=1;i<=n;i++)
            up[i][jump]=up[up[i][jump-1]][jump-1];
}

int get_lca(int a, int b)
{
    if(depth[a]<depth[b]) swap(a,b);//depth[a]>=depth[b]

    int k=depth[a]-depth[b];
    for(int i=LOG-1;i>=0;i--)
        if(k&(1<<i))
            a=up[a][i];

    if(a==b) return a;

    for(int i=LOG-1;i>=0;i--)
        if(up[a][i]!=up[b][i])
        {
            a=up[a][i];
            b=up[b][i];
        }
    return up[a][0];
}

void add(int v, int k)
{
    if(color_wierzcholki[k].empty())
    {
        color_wierzcholki[k].insert(v);
        return;
    }

    int lca_przed=get_lca(*(color_wierzcholki[k].begin()),*(color_wierzcholki[k].rbegin()));

    color_wierzcholki[k].insert(v);
    
    // int lca_po=get_lca(lca_przed, numer[v]);
    int lca_po=get_lca(*(color_wierzcholki[k].begin()),*(color_wierzcholki[k].rbegin()));

    int odl=inf;
    if(lca_przed==lca_po)
    {
        int min1=0;
        if(++color_wierzcholki[k].find(v) != color_wierzcholki[k].end()) min1=get_lca(v, *(++color_wierzcholki[k].find(v)));
        int min2=0;
        if(color_wierzcholki[k].find(v) != color_wierzcholki[k].begin()) min2=get_lca(v, *(--color_wierzcholki[k].find(v)));

        if(min1)
            odl=min(odl, abs(depth[min1]-depth[v]));
        if(min2)
            odl=min(odl, abs(depth[min2]-depth[v]));
    }
    else
        odl=abs(depth[lca_przed]-depth[lca_po])+abs(depth[v]-depth[lca_po]);

    color_odp[k]+=odl;
    return;
}

void del(int v, int k)
{
    if(color_wierzcholki[k].size()==1)
    {
        color_wierzcholki[k].erase(v);
        return;
    }

    int lca_przed=get_lca(*(color_wierzcholki[k].begin()),*(color_wierzcholki[k].rbegin()));

    color_wierzcholki[k].erase(v);
    
    // int lca_po=get_lca(lca_przed, numer[v]);
    int lca_po=get_lca(*(color_wierzcholki[k].begin()),*(color_wierzcholki[k].rbegin()));

    int odl=inf;
    if(lca_przed==lca_po)
    {
        color_wierzcholki[k].insert(v);
        int min1=0;
        if(++color_wierzcholki[k].find(v) != color_wierzcholki[k].end()) min1=get_lca(v, *(++color_wierzcholki[k].find(v)));
        int min2=0;
        if(color_wierzcholki[k].find(v) != color_wierzcholki[k].begin()) min2=get_lca(v, *(--color_wierzcholki[k].find(v)));

        if(min1)
            odl=min(odl, abs(depth[min1]-depth[v]));
        if(min2)
            odl=min(odl, abs(depth[min2]-depth[v]));
        color_wierzcholki[k].erase(v);
    }
    else
        odl=abs(depth[lca_przed]-depth[lca_po])+abs(depth[v]-depth[lca_przed]);
    

    color_odp[k]-=odl;
    return;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec_input[a].push_back(b);
        vec_input[b].push_back(a);
    }

    renumer();

    calculate_bin_lifting();

    // for(int i=1;i<=n;i++)
    // {
    //     cout<<i<<": "<<endl;
    //     cout<<numer[i]<<' '<<depth[i]<<' '<<up[i][0]<<' '<<up[i][1]<<endl;
    // }

    // cout<<get_lca(4,4);

    for(int v=1;v<=n;v++)
    {
        cin>>c;
        color_v[numer[v]]=c;
        add(numer[v], color_v[numer[v]]);
    }

    cin>>q;
    while(q--)
    {
        cin>>zap;
        if(zap=='U')
        {
            cin>>a>>b;
            a=numer[a];

            del(a,color_v[a]);

            color_v[a]=b;

            add(a,color_v[a]);

            continue;
        }
        cin>>a;
        if(color_wierzcholki[a].empty())
            cout<<-1<<'\n';
        else
            cout<<color_odp[a]<<'\n';
    }
    return 0;
}