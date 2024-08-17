#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=2e5+7;
constexpr int LOG=18;

int n,q;
int x,k;

vector<int>vec[maxn];

int up[maxn][LOG];
int depth[maxn];

void dfs(int v=1, int parent=1)
{
    up[v][0]=parent;
    for(auto &u: vec[v])
    {
        if(u==parent) continue;
        depth[u]=depth[v]+1;
        dfs(u, v);
    }
}

void calculate_bin_lifting()
{
    for(int jump=1;jump<LOG;jump++)
        for(int i=1;i<=n;i++)
            up[i][jump] = up[up[i][jump-1]][jump-1];
}

int get_lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a,b);//depth[a]>=depth[b]

    int k=depth[a]-depth[b];

    for(int i=LOG-1;i>=0;i--)
        if(k & (1<<i))
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

    cin>>n>>q;
    for(int i=1;i<=n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    dfs();
    calculate_bin_lifting();

    while(q--)
    {
        int a,b;
        cin>>a>>b;
        cout<<depth[a]+depth[b]-2*depth[get_lca(a,b)]<<'\n';
    }
    return 0;
}