#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=4e5+7;

int Z;
int n,a,b;
vector<int> vec[maxn];
pi kolor[maxn];

int NOT(int x)
{
    if(x>2*n)
        return x-2*n;
    else
        return x+2*n;
}

vector<int> graf[2*maxn];
vector<int> rev_graf[2*maxn];
void clear_graf()
{
    for(int i=1;i<=4*n;++i)
    {
        graf[i].clear();
        rev_graf[i].clear();
    }
}
bool odp[maxn];
void clear_odp()
{
    for(int i=1;i<=2*n;++i)
        odp[i]=0;
}

void dfs(int v, int ojciec=-1)
{
    if(ojciec!=-1)
    {
        graf[v].pb(ojciec);
        graf[NOT(ojciec)].pb(NOT(v));
    }
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
    }
}

bool vis[2*maxn];
void clear_vis()
{
    for(int i=1;i<=4*n;++i)
        vis[i]=0;
}

vector<int> postorder;
void get_postorder(int v)
{
    vis[v]=1;
    for(auto &u: graf[v])
    {
        if(vis[u]) continue;
        get_postorder(u);
    }
    postorder.pb(v);
}

int rep[2*maxn];
int numeruj;
void clear_rep()
{
    for(int i=1;i<=4*n;++i)
        rep[i]=-1;
    numeruj=0;
}
void mark(int v)
{
    rep[v]=numeruj;
    for(auto &u: rev_graf[v])
        if(rep[u]==-1)
            mark(u);
}

void make_graf(int start)
{
    clear_odp();
    clear_graf();
    dfs(start);
    for(int i=1;i<=n;++i)
    {
        a = kolor[i].f;
        b = kolor[i].s;

        graf[a].pb(NOT(b));
        graf[b].pb(NOT(a));
        graf[NOT(a)].pb(b);
        graf[NOT(b)].pb(a);
    }
    for(int i=1;i<=4*n;++i)
        for(auto &u: graf[i])
            rev_graf[u].pb(i);
}

bool solv(int start)
{
    make_graf(start);

    postorder.clear();
    clear_vis();
    for(int i=1;i<=4*n;++i)
        if(!vis[i])
            get_postorder(i);

    reverse(postorder.begin(),postorder.end());

    clear_rep();
    for(auto &u: postorder)
    {
        if(rep[u]==-1)
        {
            ++numeruj;
            mark(u);
        }
    }

    for(int i=1;i<=2*n;++i)
    {
        if(rep[i]==rep[NOT(i)])
            return 0;
        if(rep[i]>rep[NOT(i)])
            odp[i]=1;
    }
    return 1;
}
void TAK()
{
    cout<<"TAK\n";
    for(int i=1;i<=2*n;++i)
        cout<<odp[i]<<" ";
    cout<<"\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>Z;
    while(Z--)
    {
        cin>>n;
        for(int i=1;i<=2*n;++i)
            vec[i].clear();
        for(int i=1;i<=2*n-1;++i)
        {
            cin>>a>>b;
            vec[a].pb(b);
            vec[b].pb(a);
        }
        for(int i=1;i<=n;++i)
        {
            cin>>a>>b;
            kolor[i]={a,b};
        }
        if(solv(kolor[1].f))
            TAK();
        else if(solv(kolor[1].s))
            TAK();
        else
            cout<<"NIE\n";
    }
    return 0;
}