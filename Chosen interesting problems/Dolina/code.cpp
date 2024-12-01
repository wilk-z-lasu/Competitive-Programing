#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>
#define int long long

constexpr int maxn=1e5+7;
constexpr int inf=1e18+7;


int n,s,q,e;
int I,R;
int a[maxn],b[maxn],c;
vector<pi>vec[maxn];
bool shop[maxn];

int dp[maxn];

int licz_rep=0;
int in[maxn];
int out[maxn];
int siz[maxn];
int up[maxn];
int up_value[maxn];
void make_preorder(int v, int ojciec=-1)
{
    in[v]=++licz_rep;
    siz[v]=1;
    up[v]=ojciec;
    dp[v]=inf;
    if(shop[v]) dp[v]=0;
    for(auto &u: vec[v])
    {
        if(u.f==ojciec) continue;
        make_preorder(u.f,v);
        dp[v]=min(dp[v], dp[u.f]+u.s);
        siz[v]+=siz[u.f];
        up_value[u.f]=u.s;
    }
    out[v]=++licz_rep;
}

//HLD
int head[maxn];
int path_length[maxn];
int rep_cnt=0;
int rep[maxn];
void prepere_hld(int v, int ojciec=-1)
{
    rep[v]=++rep_cnt;
    pair<int,pi> maxi={0,{0,0}};
    for(auto &u: vec[v])
    {
        if(u.f==ojciec) continue;
        maxi=max(maxi,{siz[u.f],u});
    }
 
    if(maxi.f==0) return;
    // cout<<v<<" -> "<<maxi.s.f<<endl;
    head[maxi.s.f]=head[v];
    prepere_hld(maxi.s.f, v);
    path_length[v] = path_length[maxi.s.f] + maxi.s.s;

    for(auto &u: vec[v])
    {
        if(u.f==ojciec || u.f==maxi.s.f) continue;
        head[u.f]=u.f;
        prepere_hld(u.f, v);
    }
}

int prefix[maxn];
void make_prefixes(int v, int ojciec=-1)
{
    pair<int,pi> maxi={0,{0,0}};
    for(auto &u: vec[v])
    {
        if(u.f==ojciec) continue;
        maxi=max(maxi,{siz[u.f],u});
    }
 
    if(maxi.f==0) return;
    prefix[maxi.s.f] = min(prefix[v], dp[maxi.s.f]+path_length[maxi.s.f]);
    make_prefixes(maxi.s.f, v);

    for(auto &u: vec[v])
    {
        if(u.f==ojciec || u.f==maxi.s.f) continue;
        head[u.f]=u.f;
        prefix[u.f] = dp[u.f] + path_length[u.f];
        make_prefixes(u.f, v);
    }
}

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
        tree[poz]=min(tree[2*poz], tree[2*poz+1]);
        poz/=2;
    }
}
inline int get_min(int a, int b, int v=1, int l=1, int r=M)
{
    if(r<a || b<l) return inf;
    if(a<=l && r<=b) return tree[v];
    int mid=(l+r)/2;
    return min(get_min(a,b,2*v,l,mid), get_min(a,b,2*v+1,mid+1,r));
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>s>>q>>e;
    
    for(int i=1;i<=n-1;i++)
    {
        cin>>a[i]>>b[i]>>c;
        vec[a[i]].push_back({b[i],c});
        vec[b[i]].push_back({a[i],c});
    }

    while(s--)
    {
        cin>>c;
        shop[c]=1;
    }

    make_preorder(e);
    head[e]=e;
    prepere_hld(e);
    prefix[e]=dp[e]+path_length[e];
    make_prefixes(e);

    for(int i=1;i<=2*M;i++)
        tree[i]=inf;
    for(int i=1;i<=n;i++)
        set_tree(rep[i], dp[i]+path_length[i]);

    for(int i=1;i<=n-1;i++)
        if(in[a[i]] > in[b[i]])
            swap(a[i], b[i]);

    while(q--)
    {
        cin>>I>>R;

        int down = b[I];

        if(!(in[down] <= in[R] && out[R] <= out[down]))
        {
            cout<<"escaped\n";
            continue;
        }
        if(dp[down]==inf)
        {
            cout<<"oo\n";
            continue;
        }

        down = a[I];

        int solv=inf;
        int current_path=0;
        while(head[R]!=head[down])
        {
            solv = min(solv, prefix[R] - path_length[R] + current_path);
            current_path += (path_length[head[R]] - path_length[R] + up_value[head[R]]);
            R=up[head[R]];
        }
        if(rep[down]+1 <= rep[R])
            solv = min(solv, get_min(rep[down]+1, rep[R]) - path_length[R] + current_path);
        cout<<solv<<'\n';
    }
    return 0;
}