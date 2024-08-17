#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;

int n,q;
int v[maxn];
int a,b;
vector<int>vec[maxn];
int zapytanie,s,x;

int numeruj;
int in[maxn];
int out[maxn];

void dfs(int v=1, int parent=1)
{
    in[v]=++numeruj;
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        dfs(u, v);
    }
    out[v]=++numeruj;
}


constexpr int M=(1<<19);
int tree[2*M];
void set_tree(int poz, int val)
{
    poz=poz+M-1;
    tree[poz]=val;
    poz/=2;
    while(poz)
    {
        tree[poz]=tree[2*poz]+tree[2*poz+1];
        poz/=2;
    }
}

int get_sum(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return 0;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return get_sum(a,b,2*v,l,mid) + get_sum(a,b,2*v+1,mid+1,r);
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
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    dfs();

    for(int i=1;i<=n;i++)
    {
        // cout<<i<<": "<<in[i]<<' '<<out[i]<<endl;
        set_tree(in[i],v[i]);
        set_tree(out[i],-v[i]);
    }

    while(q--)
    {
        cin>>zapytanie;
        if(zapytanie==1)
        {
            cin>>s>>x;
            set_tree(in[s],x);
            set_tree(out[s],-x);
        }
        else
        {
            cin>>s;
            cout<<get_sum(1,out[s]-1)<<'\n';
        }
    }
    return 0;
}