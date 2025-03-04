#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

#define pb push_back
using pi = pair<int,int>;

constexpr int maxn = 5e5+7;
constexpr int inf = 1e9+7;

int n;
int k;
int x;
vector<int>vec[maxn];

int dp[maxn];
bool vis[maxn];

int bfs(int start) {
    for(int i=1;i<=n;i++)
        vis[i]=dp[i]=0;
    queue<int>q;
    q.push(start);
    vis[start]=1;

    vector<pi> con;

    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        for(const auto &u: vec[v])
        {
            if(!vis[u])
            {
                vis[u]=1;
                q.push(u);
                con.pb({v,u});
            }
        }
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])
            return inf;

    reverse(con.begin(), con.end());
    for(int i=1;i<=n;i++)
        dp[i]=1;
    for(const auto &[a,b]: con)
        dp[a]+=dp[b];
    for(const auto &[a,b]: con)
        dp[a]+=dp[b];
    
    return dp[start];
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>k;
        for(int j=1;j<=k;j++)
        {
            cin>>x;
            vec[x].pb(i);
        }
    }

    int solv=inf; 
    for(int i=1;i<=n;i++)
        solv = min(solv, bfs(i));
    cout<<solv;
    return 0;
}