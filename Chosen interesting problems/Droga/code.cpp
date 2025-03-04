#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>
#define pii pair<int,pair<int,int>>

constexpr int maxm=1e4+7;
constexpr int maxn=1e2+7;
constexpr int inf=1e9+7;


int k,n,r;
int a,b,l,t;

vector<tuple<int,int,int>>vec[maxn];
int vis[maxn][maxm];

void prepere()
{
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxm;j++)
            vis[i][j]=inf;
}
int dijkstra()
{
    priority_queue<pii>pq;
    pq.push({0,{0,1}});
    while(!pq.empty())
    {
        int odl = -pq.top().f;
        int cost = - pq.top().s.f;
        int v = pq.top().s.s;
        pq.pop();

        if(vis[v][cost]==inf)
            vis[v][cost] = odl;
        else
            continue;

        if(v==n && cost<=k)
            return odl;

        for(auto& [u, len, money]: vec[v]) 
            if(cost+money<=k)
                pq.push({-(odl+len),{-(cost+money),u}});
    }
    return -1;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>k>>n>>r;

    for(int i=1;i<=r;i++)
    {
        cin>>a>>b>>l>>t;
        vec[a].push_back({b,l,t});
    }
    prepere();
    cout<<dijkstra();
    return 0;
}