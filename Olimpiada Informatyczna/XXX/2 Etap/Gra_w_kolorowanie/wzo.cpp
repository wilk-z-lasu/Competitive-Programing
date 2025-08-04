#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 5e5+7;

int n;
int a,b;
int Sa, Sb, q;
char z, t;
int w;

vector<int>vec[maxn];

int siz[maxn];
void dfs(int v=1, int ojciec=-1)
{
    siz[v]=1;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
        siz[v]+=siz[u];
    }
}

int cen1;
int cen2;
int get_centroid(int v=1, int ojciec=-1)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        if(2*siz[u] == n)
            cen2=u;
        if(2*siz[u] > n)
            return get_centroid(u,v);
    }
    return v;
}

int odl[3][maxn];
int rep[maxn];
void mark_odl(int v, int opt, int ojciec=-1)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        odl[opt][u] = odl[opt][v] + 1;
        mark_odl(u,opt,v);
    }
}

constexpr int M = (1<<19);
struct Tree
{
    int tree[2*M];
    void prepere()
    {
        for(int i=1;i<2*M;++i)
            tree[i]=0;
    }
    void add_tree(int poz, int val)
    {
        poz = poz + M - 1;
        tree[poz] += val;
        poz/=2;
        while(poz)
        {
            tree[poz] = tree[2*poz] + tree[2*poz + 1];
            poz/=2;
        }
    }
    int get_tree(int a, int b, int v=1, int l=1, int r=M)
    {
        if(r<a || b<l) return 0;
        if(a<=l && r<=b)
            return tree[v];
        int mid = (l+r)/2;
        return get_tree(a,b,2*v,l,mid) + get_tree(a,b,2*v+1,mid+1,r);
    }
} A1,B1,A2,B2;

int taken[maxn];
long long solv=0;
void add_B(int x)
{
    if(++taken[x]==2) --solv;
    // cout<<"add_B";
    if(rep[x]==1)
    {
        // cout<<"[1] "<<odl[1][x]<<endl;
        B1.add_tree(odl[1][x], +1);
        solv += A1.get_tree(1,odl[1][x]);
        if(1 <= odl[1][x]-1) solv += A2.get_tree(1,odl[1][x]-1);
    }
    else
    {
        // cout<<"[2] "<<odl[2][x]<<endl;
        B2.add_tree(odl[2][x], +1);
        solv += A2.get_tree(1,odl[2][x]);
        if(1 <= odl[2][x]-1) solv += A1.get_tree(1,odl[2][x]-1);
    }
}
void del_B(int x)
{
    if(--taken[x]==1) ++solv;
    if(rep[x]==1)
    {
        B1.add_tree(odl[1][x], -1);
        solv -= A1.get_tree(1,odl[1][x]);
        if(1 <= odl[1][x]-1) solv -= A2.get_tree(1,odl[1][x]-1);
    }
    else
    {
        B2.add_tree(odl[2][x], -1);
        solv -= A2.get_tree(1,odl[2][x]);
        if(1 <= odl[2][x]-1) solv -= A1.get_tree(1,odl[2][x]-1);
    }
}

void add_A(int x)
{
    if(++taken[x]==2) --solv;
    // cout<<"add_A";
    if(rep[x]==1)
    {
        // cout<<"[1] "<<odl[1][x]<<endl;
        A1.add_tree(odl[1][x], +1);
        solv += B1.get_tree(odl[1][x], M);
        if(odl[1][x]+1 <= M) solv += B2.get_tree(odl[1][x]+1,M);
    }
    else
    {
        // cout<<"[2] "<<odl[2][x]<<endl;
        A2.add_tree(odl[2][x], +1);
        solv += B2.get_tree(odl[2][x], M);
        if(odl[2][x]+1 <= M) solv += B1.get_tree(odl[2][x]+1, M);
    }
}
void del_A(int x)
{
    if(--taken[x]==1) ++solv;
    if(rep[x]==1)
    {
        A1.add_tree(odl[1][x], -1);
        solv -= B1.get_tree(odl[1][x], M);
        if(odl[1][x]+1 <= M) solv -= B2.get_tree(odl[1][x]+1,M);
    }
    else
    {
        A2.add_tree(odl[2][x], -1);
        solv -= B2.get_tree(odl[2][x], M);
        if(odl[2][x]+1 <= M) solv -= B1.get_tree(odl[2][x]+1, M);
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    dfs();
    cen1 = get_centroid();

    // cout<<cen1<<' '<<cen2<<endl;
    if(cen2==0)
        cen2=cen1;
    
    odl[1][cen1] = 1;
    mark_odl(cen1, 1);
    odl[2][cen2] = 1;
    mark_odl(cen2, 2);

    for(int i=1;i<=n;++i)
    {
        if(odl[1][i] <= odl[2][i])
            rep[i] = 1;
        else
            rep[i] = 2;
    }
        
    // for(int i=1;i<=n;++i)
    //     cout<<i<<": "<<odl[1][i]<<' '<<odl[2][i]<<" <- "<<rep[i]<<endl;

    A1.prepere();
    A2.prepere();
    B1.prepere();
    B2.prepere();

    cin>>Sa>>Sb>>q;
    while(Sa--)
    {
        cin>>w;
        add_A(w);
    }
    while(Sb--)
    {
        cin>>w;
        add_B(w);
    }
    cout<<solv<<'\n';
    while(q--)
    {
        cin>>z>>t>>w;
        if(z=='A')
        {
            if(t=='+')
                add_A(w);
            else if(t=='-')
                del_A(w);
        }
        else if(z=='B')
        {
            if(t=='+')
                add_B(w);
            else if(t=='-')
                del_B(w);
        }
        cout<<solv<<'\n';
    }
}