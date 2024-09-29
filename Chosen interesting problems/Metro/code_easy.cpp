#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1000007;

int odp;
int n,l;
vector<int> vec[maxn];
int dp[maxn];
int layer[maxn];
int vis[maxn];

queue<int>q;
void bfs()
{
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        layer[dp[v]]++;

        for(auto &u: vec[v])
        {
            vis[u]++;
            if(vis[u]+1 == vec[u].size())
            {
                dp[u]=dp[v]+1;
                q.push(u);
            }
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>l;
    for(int i=1;i<=n-1;i++)
    {
        int a,b; cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    for(int i=1;i<=n;i++)
        if(vec[i].size()==1)
            q.push(i);
    bfs();

    int solv=0;
    for(int i=0;i<=n;i++)
        solv+=min(2*l, layer[i]);
    cout<<solv;
    return 0;
}