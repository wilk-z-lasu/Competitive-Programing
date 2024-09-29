#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1e5+7;

int n,m;
int a,b;
int q;
int c;
vector<int>vec[maxn];

int dp[maxn][2][2];//[v][kto gra][dlugosc ruchu-1]
void licz(int v)
{
    for(auto &u: vec[v])
    {
        if(dp[u][1][0])
            dp[v][1][1]=1;
        if(!dp[u][0][1])
            dp[v][1][0]=1;

        if(dp[u][0][0])
            dp[v][0][1]=1;
        if(!dp[u][1][1])
            dp[v][0][0]=1;
    }
}

bool vis[maxn];
vector<int>toposort;

void sort_topologically(int v)
{
    vis[v]=1;
    for(auto &u: vec[v])
    {
        if(vis[u]) continue;
        sort_topologically(u);
    }
    toposort.push_back(v);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
    }

    for(int i=1;i<=n;i++)
        if(!vis[i])
            sort_topologically(i);

    for(auto &u: toposort)
        licz(u);

    cin>>q;
    while(q--)
    {
        cin>>c;
        if(dp[c][1][1])
            cout<<"Bitek\n";
        else
            cout<<"Bajtek\n";
    }

    return 0;
}