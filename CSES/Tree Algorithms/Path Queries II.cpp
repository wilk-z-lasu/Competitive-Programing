#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
 
constexpr int maxn=2e5+7;
 
int n,q;
int v[maxn];
vector<int>vec[maxn];
int zapytanie,s,x;
 
//Segment tree
constexpr int M=(1<<18);
int tree[2*M];
inline void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz]=max(tree[2*poz], tree[2*poz+1]);
        poz/=2;
    }
}
inline int get_max(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return max(get_max(a,b,2*v,l,mid), get_max(a,b,2*v+1,mid+1,r));
}
 
//HLD
int siz[maxn];
int parent[maxn];
int depth[maxn];

int head[maxn];
int numeruj=0;
int number[maxn];
inline void prepere(int v=1, int p=1)
{
    siz[v]=1;
    parent[v]=p;
    depth[v]=depth[p]+1;
    for(auto &u: vec[v])
    {
        if(u==p) continue;
        prepere(u,v);
        siz[v]+=siz[u];
    }
}
inline void dfs(int v=1)
{
    number[v]=++numeruj;
    if(vec[v].size()==1 && vec[v][0]==parent[v]) return;
 
    pair<int,int>maxi={0,0};
    for(auto &u: vec[v])
    {
        if(u==parent[v]) continue;
        maxi=max(maxi,{siz[u],u});
    }
 
    head[maxi.s]=head[v];
    dfs(maxi.s);
 
    for(auto &u: vec[v])
    {
        if(u==parent[v] || u==maxi.s) continue;
        head[u]=u;
        dfs(u);
    }
}
inline void HLD()
{
    prepere();
    head[1]=1;
    dfs();
}
 
inline int max_path(int a, int b)
{
    int odp=0;
    while(head[a]!=head[b])
    {
        if(depth[head[a]]>depth[head[b]]) swap(a,b);
        odp=max(odp, get_max(number[head[b]], number[b]));
        b=parent[head[b]];
    }

    if(depth[a]>depth[b]) swap(a,b);
    odp=max(odp, get_max(number[a], number[b]));
    return odp;
}
 
inline void update_node(int node, int value)
{
    set_tree(number[node], value);
}
 
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>v[i];
    for(int i=1;i<=n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    
    HLD();
 
    for(int i=1;i<=n;i++)
        update_node(i, v[i]);
 
    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie==1)
        {
            cin>>s>>x;
            update_node(s, x);
        }
        else
        {
            int a,b;
            cin>>a>>b;
            cout<<max_path(a,b)<<' ';
        }
    }
    return 0;
}