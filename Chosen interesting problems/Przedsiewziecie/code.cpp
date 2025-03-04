#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

#define pb push_back
using pi = pair<int,int>;

constexpr int maxn = 1e5+7;

int n;
int k;
int Czas[maxn];
int x;
vector<int>vec[maxn];
vector<pi> con;
int q;
int m,d;

bool vis[maxn];
vector<int>postorder;

void dfs(int v) {
    vis[v]=1;
    for(auto &u: vec[v])
        if(!vis[u])
            dfs(u);
    postorder.push_back(v);
}

int Order[maxn];
int dp[maxn];

int time_up[maxn];
int extra_time[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>Czas[i]>>k;
        for(int j=1;j<=k;j++)
        {
            cin>>x;
            vec[i].pb(x);
            con.pb({i,x});
        }
    }

    //toposort
    for(int i=1;i<=n;i++)
        if(!vis[i])
            dfs(i);

    for(int i=0;i<=n-1;i++)
        Order[postorder[i]]=i;

    for(auto &[a,b]: con)
        if(Order[a] < Order[b])
        {
            cout<<"CYKL";
            return 0;
        }

    for(int v: postorder)
    {
        for(int u: vec[v])
            dp[v] = max(dp[v], dp[u]);
        dp[v] += Czas[v]; 
    }

    int solv=0;
    for(int i=1;i<=n;i++)
        solv = max(solv, dp[i]);
    cout<<solv<<'\n';

    reverse(postorder.begin(), postorder.end());


    for(int v: postorder)
    {
        extra_time[v] = solv-time_up[v]-dp[v];
        for(int u: vec[v])
            time_up[u] = max(time_up[u], time_up[v]+Czas[v]);
    }

    cin>>q;
    while(q--)
    {
        cin>>m>>d;
        if(d > extra_time[m])
            cout<<"TAK\n";
        else
            cout<<"NIE\n";
    }
    return 0;
}