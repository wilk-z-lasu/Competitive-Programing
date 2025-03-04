#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e5+7;

int n,m;

int a,b;
int t[maxn];
vector<int>vec[maxn];
pair<int,int> zmiana[maxn];
int zmiana_v[maxn];

int e, ti;

int numeruj;
int numer[maxn];
int siz[maxn];

void renumer(int v=1, int parent=1)
{
    ++numeruj;
    numer[v]=numeruj;
    siz[numer[v]]++;

    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        renumer(u,v);
        siz[numer[v]] += siz[numer[u]];
    }
}

constexpr int M=(1<<17);
int tree[2*M];
int push[2*M];


void set_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v]+=val;
        push[v]+=val;
        return;
    }
    int mid=(l+r)/2;
    tree[2*v]+=push[v];
    push[2*v]+=push[v];
    tree[2*v+1]+=push[v];
    push[2*v+1]+=push[v];
    push[v]=0;

    set_tree(a,b,val,2*v,l,mid);
    set_tree(a,b,val,2*v+1,mid+1,r);
    tree[v]=max(tree[2*v],tree[2*v+1]);
}

int max_tree()
{
    return tree[1];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b>>t[i];
        vec[a].push_back(b);
        vec[b].push_back(a);
        zmiana[i]={a,b};
    }

    cin>>m;

    renumer();

    for(int i=1;i<=n-1;i++)
    {
        if(numer[zmiana[i].f]<numer[zmiana[i].s])
            zmiana_v[i]=numer[zmiana[i].s];
        else
            zmiana_v[i]=numer[zmiana[i].f];
    }

    for(int i=1;i<=n-1;i++)
        numer[zmiana_v[i]]=zmiana_v[i];

    for(int i=1;i<=n-1;i++)
        set_tree(zmiana_v[i], zmiana_v[i]+siz[zmiana_v[i]]-1, t[i]);

    for(int i=1;i<=m;i++)
    {
        cin>>e>>ti;
        set_tree(zmiana_v[e],zmiana_v[e]+siz[zmiana_v[e]]-1, ti-t[e]);
        t[e]=ti;
        cout<<max_tree()<<'\n';
    }

    return 0;
}