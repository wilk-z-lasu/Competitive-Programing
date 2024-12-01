#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=3007;

int n,m;
ll mod;
int a,b;

vector<int>vec[maxn];
vector<int>graf[maxn];

int dp[maxn][maxn][4];//[0]-niebo [x]-x'ty syn jest nademna

int order(int v, int ojciec)
{
    for(int i=0;i<vec[v].size();i++)
        if(vec[v][i] == ojciec)
            return i+1;
}

void licz(int v, vector<int>& opt)
{
    for(int rep=1;rep<=n;rep++)
    {
        if(vec[rep].size() > graf[v].size()) continue;
        if(vec[rep].size()==1) 
        {
            int syn=vec[rep][0];
            for(auto &u: opt)
                dp[v][rep][0] = (dp[v][rep][0] + dp[u][syn][order(syn,rep)])%mod;
            dp[v][rep][1]=1;
        }
        else if(vec[rep].size()==2)
        {
            int x1=vec[rep][0];
            int x2=vec[rep][1];

            for(auto &u: opt)
            {
                dp[v][rep][1] = (dp[v][rep][1] + dp[u][x2][order(x2,rep)])%mod;
                dp[v][rep][2] = (dp[v][rep][2] + dp[u][x1][order(x1,rep)])%mod;
            }
            for(auto &i1: opt)
            {
                for(auto &i2: opt)
                {
                    if(i1==i2) continue;
                    dp[v][rep][0] = ((ll)dp[v][rep][0] + (ll)dp[i1][x1][order(x1,rep)]*(ll)dp[i2][x2][order(x2,rep)])%mod;
                }
            }
        }
        else if(vec[rep].size()==3)
        {
            int x1=vec[rep][0];
            int x2=vec[rep][1];
            int x3=vec[rep][2];

            for(auto &i1: opt)
            {
                for(auto &i2: opt)
                {
                    if(i1==i2) continue;
                    dp[v][rep][1] = ((ll)dp[v][rep][1] + (ll)dp[i1][x2][order(x2,rep)]*(ll)dp[i2][x3][order(x3,rep)])%mod;
                    dp[v][rep][2] = ((ll)dp[v][rep][2] + (ll)dp[i1][x1][order(x1,rep)]*(ll)dp[i2][x3][order(x3,rep)])%mod;
                    dp[v][rep][3] = ((ll)dp[v][rep][3] + (ll)dp[i1][x1][order(x1,rep)]*(ll)dp[i2][x2][order(x2,rep)])%mod;
                }
            }
        }
    }
}
void dfs(int v, int ojciec=-1)
{
    for(auto &u: graf[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
    }

    vector<int>wolne;
    for(auto &u: graf[v])
    {
        if(u==ojciec) continue;
        wolne.push_back(u);
    }
    licz(v, wolne);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>mod;
    if(n==1)
    {
        cout<<m%mod;
        return 0;
    }
    
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    for(int i=1;i<=m-1;i++)
    {
        cin>>a>>b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }

    int leaf;
    for(int i=1;i<=m;i++)
        if(graf[i].size()==1)
            leaf=i;

    dfs(leaf);

    int solv=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            solv = (solv + dp[i][j][0])%mod;
    cout<<solv;
    return 0;
}