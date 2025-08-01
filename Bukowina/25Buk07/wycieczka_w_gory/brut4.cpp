#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e5+7;
constexpr int LOG = 18;

int n,k;

vector<pi>vec[maxn];

pi dfs(int v=1, int ojciec=-1)
{
    pi maxi = {0,v};
    for(auto &[u,cost]: vec[v])
    {
        if(u==ojciec) continue;
        pi Next = dfs(u,v);
        maxi = max(maxi, {Next.f+cost, Next.s});
    }
    return maxi;
}

int dp[maxn];
int up[maxn][LOG];
int depth[maxn];
void prepere(int v=1)
{
    for(auto &[u,cost]: vec[v])
    {
        if(u == up[v][0]) continue;
        up[u][0] = v;
        depth[u] = depth[v]+1;
        dp[u] = dp[v] + cost;
        prepere(u);
    }
}
void bin_lifting()
{
    for(int log = 1; log < LOG; ++log)
        for(int i=1;i<=n;++i)
            up[i][log] = up[up[i][log-1]][log-1];
}

int get_lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a,b);//depth[a]>=depth[b]

    int k=depth[a]-depth[b];
    for(int i=LOG-1;i>=0;i--)
        if(k&(1<<i))
            a=up[a][i];
    if(a==b) return a;

    for(int i=LOG-1;i>=0;i--)
        if(up[a][i] != up[b][i])
        {
            a=up[a][i];
            b=up[b][i];
        }
    return up[a][0];
}

int get_odl(int a, int b)
{
    return dp[a] + dp[b] - 2*dp[get_lca(a,b)];
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n-1;++i)
    {
        int a,b,c;
        cin>>a>>b>>c;
        vec[a].pb({b,c});
        vec[b].pb({a,c});
    }

    pair<int,vector<int>> solv={0,{0,0,0,0}};
    up[1][0]=1;
    prepere();
    bin_lifting();

    //FOR k = 4
    for(int a=1;a<=n;++a)
        for(int b=a+1;b<=n;++b)
            for(int c=b+1;c<=n;++c)
                for(int d=c+1;d<=n;++d)
                    solv = max(solv, 
                    {get_odl(a,b)+get_odl(a,c)+get_odl(a,d)
                    +get_odl(b,c)+get_odl(b,d)
                    +get_odl(c,d),{a,b,c,d}});
    cout<<solv.f<<endl;
    cout<<solv.s[0]<<endl;
    cout<<solv.s[1]<<endl;
    cout<<solv.s[2]<<endl;
    cout<<solv.s[3]<<endl;


    //FOR k = 3
    // for(int a=1;a<=n;++a)
    //     for(int b=a+1;b<=n;++b)
    //         for(int c=b+1;c<=n;++c)
    //             solv = max(solv, 
    //             get_odl(a,b)+get_odl(a,c)
    //             +get_odl(b,c));
    // cout<<solv;
}