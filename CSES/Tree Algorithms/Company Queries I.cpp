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

void dfs(int v=1)
{
    for(auto &u: vec[v])
    {
        depth[u]=depth[v]+1;
        dfs(u);
    }
}
void calculate_bin_lifting()
{
    for(int jump=1;jump<LOG;jump++)
        for(int i=1;i<=n;i++)
            up[i][jump] = up[up[i][jump-1]][jump-1];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    up[1][0]=1;
    for(int i=2;i<=n;i++)
    {
        cin>>up[i][0];
        vec[up[i][0]].push_back(i);
    }

    calculate_bin_lifting();
    dfs();

    while(q--)
    {
        cin>>x>>k;
        if(depth[x]<k)
        {
            cout<<-1<<' ';
            continue;
        }
        for(int i=LOG-1;i>=0;i--)
            if((1<<i)&k)
                x=up[x][i];
        cout<<x<<'\n';
    }
    return 0;
}