#include <bits/stdc++.h>
using namespace std;

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e9+7;
constexpr int maxn = 2e5+7;

int n;
int L[maxn];
int a,b;
vector<int>vec[maxn];
vector<int>grup[maxn];

int siz[maxn];
int rep[maxn];
int num = 0;
void dfs(int v=1, int ojciec=-1)
{
    rep[v] = ++num;
    siz[v]=1;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
        siz[v] += siz[u];
    }
}

bool win[maxn];
constexpr int M = (1<<18);
struct min_tree{
    int tree[2*M];
    void preproces()
    {
        for(int i=0;i<2*M;++i)
            tree[i] = inf;
    }
    void set_tree(int poz, int val)
    {
        poz = poz+M;
        tree[poz] = val;
        poz/=2;
        while(poz)
        {
            tree[poz]=min(tree[2*poz], tree[2*poz+1]);
            poz/=2;
        }
    }
    int get(int a, int b, int v=1, int l=0, int r=M-1)
    {
        if(r < a || b < l) return inf;
        if(a<=l && r<=b) return tree[v];
        int mid = (l+r)/2;
        return min(get(a,b,2*v, l, mid), get(a,b,2*v+1, mid+1, r));
    }
}mini1, mini2;

struct max_tree{
    int tree[2*M];
    void preproces()
    {
        for(int i=0;i<2*M;++i)
            tree[i] = -inf;
    }
    void set_tree(int poz, int val)
    {
        poz = poz+M;
        tree[poz] = val;
        poz/=2;
        while(poz)
        {
            tree[poz]=max(tree[2*poz], tree[2*poz+1]);
            poz/=2;
        }
    }
    int get(int a, int b, int v=1, int l=0, int r=M-1)
    {
        if(r < a || b < l) return -inf;
        if(a<=l && r<=b) return tree[v];
        int mid = (l+r)/2;
        return max(get(a,b,2*v, l, mid), get(a,b,2*v+1, mid+1, r));
    }
}maxi1, maxi2;

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=1; i<=n; ++i)
        cin>>L[i]; 
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }
    dfs();
    for(int i=1;i<=n;++i)
        grup[L[i]].pb(i);
    
    mini1.preproces();
    maxi1.preproces();
    mini2.preproces();
    maxi2.preproces();

    for(int i=n;i>=1;--i)
    {
        if(grup[i].empty()) continue;
        for(auto &v: grup[i])
        {
            int l = min(mini1.get(0, rep[v]-1), mini1.get(rep[v]+siz[v], M-1));
            int r = max(maxi1.get(0, rep[v]-1), maxi1.get(rep[v]+siz[v], M-1));
            if(!(l < rep[v] || r > rep[v]+siz[v]-1) && min(mini2.get(0, rep[v]-1), mini2.get(rep[v]+siz[v], M-1)) != inf) 
                win[v] = 1;
        }

        for(auto &v: grup[i])
        {
            mini1.set_tree(rep[v], min(mini2.get(0, rep[v]-1), mini2.get(rep[v]+siz[v], M-1)));
            maxi1.set_tree(rep[v], max(maxi2.get(0, rep[v]-1), maxi2.get(rep[v]+siz[v], M-1)));
        }
        for(auto &v: grup[i])
        {
            mini2.set_tree(rep[v], rep[v]);
            maxi2.set_tree(rep[v], rep[v]);
        }
    }
    vector<int>solv;
    for(int i=2;i<=n;++i)
        if(win[i])
            solv.pb(i);
    cout<<sz(solv)<<'\n';
    for(auto &u: solv)
        cout<<u<<' ';
    return 0;
}