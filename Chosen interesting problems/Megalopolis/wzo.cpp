#include <bits/stdc++.h>
using namespace std;

#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=250000+7;

int n,m;
vector<int>vec[maxn];

constexpr int M=(1<<18);
int tree[M*2];
int set_tree(int a, int b, int v=1, int l=1, int r=M)
{
    if(b<l || r<a) return 0;
    if(a<=l && r<=b)
    {
        tree[v]++;
        return 0;
    }
    int mid=(l+r)/2;
    set_tree(a,b,v*2,l,mid);
    set_tree(a,b,v*2+1,mid+1,r);
    return 0;
}
int get_tree(int poz)
{
    poz=poz+M-1;
    int res=0;
    while(poz>=1)
    {
        res+=tree[poz];
        poz/=2;
    }
    return res;
}
int siz[maxn];
int depth[maxn];
int preorder[maxn], numer=0;
void dfs(int v , int ojciec = -1, int d = 0)
{
    preorder[v] = ++numer;
    siz[v]=1;
    depth[v]=d;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v,d+1);
        siz[v]+=siz[u];
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n-1;++i)
    {
        int a,b;
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }
    dfs(1);
    cin>>m;
    for(int i=1;i<=m+n-1;++i)
    {
        char znak; cin>>znak;
        if(znak=='A')
        {
            int a,b;
            cin>>a>>b;
            // b > a, so b is further from root, mark edge above b as highway
            set_tree(preorder[b], preorder[b]+siz[b]-1);
        }
        else
        {
            int v;
            cin>>v;
            // depth[v] = total edges on path, get_tree = highways on path
            cout<<depth[v]-get_tree(preorder[v])<<"\n";
        }
    }
    return 0;
}