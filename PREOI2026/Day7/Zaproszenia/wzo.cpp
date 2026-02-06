#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;

constexpr int M=(1<<17);
pi tree[2*M];
int lazy[2*M];
void Push(int v)
{
    if(lazy[v]==0) return;
    tree[2*v].f+=lazy[v];
    lazy[2*v]+=lazy[v];
    tree[2*v+1].f+=lazy[v];
    lazy[2*v+1]+=lazy[v];
    lazy[v]=0;
}
void add_tree(int a, int b, int val, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return;
    if(a<=l && r<=b)
    {
        tree[v].f+=val;
        lazy[v]+=val;
        return;
    }
    Push(v);
    int mid=(l+r)/2;
    add_tree(a,b,val,2*v,l,mid);
    add_tree(a,b,val,2*v+1,mid+1,r);
    tree[v]=max(tree[2*v],tree[2*v+1]);
}


int n;
int a,b,l,q,P;

vector<pi> vec[maxn];
int siz[maxn];
int preorder[maxn];
int parent[maxn];
int up[maxn];
int vis[maxn];

int timer=0;
void dfs(int v=1, int p=0, int d=0)
{
    up[v]=d;
    parent[v]=p;
    preorder[v]=++timer;
    siz[v]=1;
    for(auto& u: vec[v])
    {
        if(u.f==p) continue;
        dfs(u.f,v,u.s);
        siz[v]+=siz[u.f];
    }
}
void make_tree(int v=1)
{
    add_tree(preorder[v],preorder[v]+siz[v]-1,up[v]);
    for(auto& u: vec[v])
    {
        if(u.f==parent[v]) continue;
        make_tree(u.f);
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T; cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n-1;++i)
        {
            cin>>a>>b>>l;
            vec[a].pb({b,l});
            vec[b].pb({a,l});
        }

        dfs();

        for(int i=1;i<2*M;++i)
            tree[i]={0,0}, lazy[i]=0;
        for(int i=1;i<=n;++i)
            tree[M+preorder[i]-1]={0,i};
        for(int i=M-1;i>=1;--i)
            tree[i]=max(tree[2*i],tree[2*i+1]);
        make_tree();

        int sum = 0;
        for(int i=1;i<=n;++i)
            sum += 2*up[i];
            
        vector<int> res;
        vis[1]=1;
        while(tree[1].f>0)
        {
            res.pb(tree[1].f);
            int v=tree[1].s;
            while(!vis[v])
            {
                vis[v]=1;
                add_tree(preorder[v], preorder[v]+siz[v]-1, -up[v]);
                v=parent[v];
            }
        }
        res.pb(0);
        sort(res.begin(), res.end());

        vector<int> suf(sz(res)+1);
        suf[sz(res)]=0;
        for(int i=sz(res)-1;i>=0;--i)
            suf[i]=suf[i+1]+res[i];

        // cout<<"sum: "<<sum<<endl;
        // cout<<"sz(res): "<<sz(res)<<endl;

        int licz=0;
        for(int i=2;i<=n;++i)
            if(sz(vec[i])==1 && vec[i][0].f==parent[i]) licz++;

        cin>>q;
        while(q--)
        {
            cin>>P;
            auto it=upper_bound(res.begin(), res.end(), P);
            if(it==res.end())
                cout<<sum - res.back()<<"\n";
            else
                cout<<sum - suf[it - res.begin()] + P * (res.end() - it - 1)<<"\n";
        }

        for(int i=1;i<=n;++i)
        {
            vec[i].clear();
            vis[i]=0;
        }
        timer = 0;
    }
    return 0;
}