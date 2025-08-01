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

pi preproces(int v=1, int ojciec=-1)
{
    pi maxi = {0,v};
    for(auto &[u,cost]: vec[v])
    {
        if(u==ojciec) continue;
        pi Next = preproces(u,v);
        maxi = max(maxi, {Next.f+cost, Next.s});
    }
    return maxi;
}

int dis[maxn];
int up[maxn][LOG];
int depth[maxn];
void prepere(int v=1)
{
    for(auto &[u,cost]: vec[v])
    {
        if(u == up[v][0]) continue;
        up[u][0] = v;
        depth[u] = depth[v]+1;
        dis[u] = dis[v] + cost;
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

void solv_k_2_3()
{
    int a = preproces(1).s;
    pi h = preproces(a);
    int b = h.s;
    int odl = h.f;

    if(k==2)
    {
        cout<<odl;
        exit(0);
    }

    int solv=0;
    up[1][0]=1;
    prepere();
    bin_lifting();
    for(int i=1;i<=n;++i)
    {
        if(i==a || i==b) continue;

        int tmp_odl = odl;

        tmp_odl += dis[a] + dis[i] - 2*dis[get_lca(a,i)];
        tmp_odl += dis[b] + dis[i] - 2*dis[get_lca(b,i)];

        // cout<<i<<": "<<tmp_odl<<endl;
        solv = max(solv, tmp_odl);
    }
    if(k==3)
    {
        cout<<solv;
        exit(0);
    }
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

    solv_k_2_3();
}