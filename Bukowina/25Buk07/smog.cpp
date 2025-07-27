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

constexpr int maxn = 1e4+7;
constexpr int maxh = 1e3+7;


int n;
int h[maxn];
int a, b, G;
vector<int>vec[maxn];

constexpr int LOG = 15;
int depth[maxn];
int up[maxn][LOG];
int dp[maxh][maxn];
int ile[2*maxh];
bitset<maxh> pos;

void dfs(int v)
{
    for(int i=1;i<maxh;++i)
        dp[i][v] = dp[i][up[v][0]];
    ++dp[h[v]][v];

    for(auto &u: vec[v])
    {
        if(u==up[v][0]) continue;
        up[u][0]=v;
        depth[u] = depth[v]+1;
        dfs(u);
    }
}
void bin_lift()
{
    for(int log=1;log<LOG;++log)
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

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>h[i];
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    up[1][0]=1;
    dfs(1);
    bin_lift();
    up[1][0]=0;
    int q;
    cin>>q;
    while(q--)
    {
        cin>>a>>b>>G;
        int LCA=get_lca(a, b);
        for(int i=1;i<maxh;++i)
            ile[i] = 0;
        for(int i=1;i<maxh;++i)
            ile[i] = dp[i][a] + dp[i][b] - dp[i][up[LCA][0]] - dp[i][LCA];
        int maxi=0;
        int k=0;
        for(int i=maxh-1;i>=1;--i)
        {
            if(ile[i] > 0)
            {
                maxi = i;
                break;
            }
        }
        k = ile[maxi];
        ile[maxi] = 0;

        for(int i=1;i<maxh;++i)
        {
            if(ile[i] > 2)
            {
                --ile[i];
                ile[2*i] += ile[i]/2;
                ile[i] %= 2;
                ++ile[i];
            }
        }
        pos.reset();
        pos[0]=1;
        for(int i=1;i<maxh;++i)
        {
            for(int j=1;j<=ile[i];++j)
                pos |= (pos<<i);
        }
        bool flag=0;
        for(int i=0;i<=G;++i)
        {
            if(pos[i]==0) continue;
            int G_prim = G - i;
            if(G_prim%maxi == 0 && (G_prim/maxi)%2 == k%2 && (G_prim/maxi)<=k)
                flag=1;
        }
        if(flag) cout<<"TAK"<<'\n';
        else cout<<"NIE"<<'\n';
    }
}