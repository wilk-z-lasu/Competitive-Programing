#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1000+7;

int n,m;
int a,b;
vector<int>vec[maxn];

bool diameter[maxn];

void NIE()
{
    cout<<"NIE";
    exit(0);
}

pair<int,int> dfs(int v=1, int ojciec=-1)
{
    pair<int,int> solv={0,v};
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        solv = max(solv, dfs(u,v));
    }
    solv.f++;
    return solv;
}

int depth[maxn];
void licz_depth(int v, int ojciec=-1)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        licz_depth(u,v);
        depth[v]=max(depth[v],depth[u]);
    }
    depth[v]++;
}

vector<int>solv;
void make_solv(int v, int ojciec)
{
    solv.push_back(v);
    pair<int,int> next={0,0};
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        next = max(next, {depth[u], u});
    }

    for(auto &u: vec[v])
    {
        if(u==ojciec || u==next.s) continue;
        if(depth[u]>2) NIE();
        if(depth[u]==2)
        {
            solv.push_back(u);
            solv.push_back(v);
        }
    }
    if(next.f==1)
        return;
    else
        make_solv(next.s, v);
}


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    if(m!=n-1)
        NIE();

    if(n==1)
    {
        cout<<"TAK\n";
        cout<<1<<'\n';
        cout<<1;
        return 0;
    }
    if(n==2)
    {
        cout<<"TAK\n";
        cout<<2<<'\n';
        cout<<1<<' '<<1;
        return 0;
    }

    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    int diameter_end = dfs().s;

    int start = vec[diameter_end][0];

    licz_depth(start);

    // for(int i=1;i<=n;i++)
    //     cout<<i<<": "<<depth[i]<<endl;

    make_solv(start, diameter_end);

    cout<<"TAK\n";
    cout<<2*solv.size()<<'\n';
    for(auto &u: solv)
        cout<<u<<' ';
    reverse(solv.begin(), solv.end());
    for(auto &u: solv)
        cout<<u<<' ';
    return 0;
}
//veni vini vici