constexpr int maxn=2e5+7;
constexpr int LOG=18;

int up[maxn][LOG];
int depth[maxn];

void dfs(int v=1)
{
    for(auto &u: vec[v])
    {
        depth[u]=depth[v]+1;
        dfs(u);
    }
}

void calculate_bin_lifting()//O(n*log(n))
{
    for(int jump=1;jump<LOG;jump++)
        for(int i=1;i<=n;i++)
            up[i][jump] = up[up[i][jump-1]][jump-1];
}

int get_lca(int a, int b)//O(log(n))
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
