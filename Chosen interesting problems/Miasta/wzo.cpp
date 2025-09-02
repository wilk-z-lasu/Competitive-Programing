// O((3^k)*(n+m)*log(m))
#include <bits/stdc++.h>
using namespace std;
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = (1e5 + 7);
constexpr int inf = (1e18 + 7);
constexpr int maxk = 5;
constexpr int maxmask = (1 << 5);

int n,k,m;
int important[5];
int a,b,c;

vector<pi>vec[maxn];

int dp[maxmask][maxn];

void Dijkstra(int mask)
{
    priority_queue<pi, vector<pi>, greater<pi>>pq;
    for(int i=1;i<=n;++i)
        pq.push({dp[mask][i], i});
    while(!pq.empty())
    {
        int odl = pq.top().f;
        int v = pq.top().s;
        pq.pop();
        
        if(odl > dp[mask][v]) continue;

        dp[mask][v] = odl;
        for(auto &xd: vec[v])
        {
            int u = xd.f;
            int cost = xd.s;
            if(dp[mask][u] > dp[mask][v] + cost)
                pq.push({dp[mask][v] + cost, u});
        }
    }
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>k>>m;
    for(int i=0;i<k;++i)
        cin>>important[i];
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b>>c;
        vec[a].pb({b,c});
        vec[b].pb({a,c});
    }

    for(int mask = 0; mask < (1 << k); ++mask)
        for(int i=1;i<=n;++i)
            dp[mask][i] = inf;

    for(int i = 0; i < k; ++i)
    {
        dp[1 << i][important[i]] = 0;
        Dijkstra(1 << i);
        // cout<<"dp[1 << i][2] = "<<dp[1 << i][2]<<'\n';
        // cout<<"-----"<<i<<"-----"<<endl;
        // for(int j=1;j<=n;++j)
        //     cout<<dp[1 << i][j]<<" ";
        // cout<<endl;
    }


    for(int mask = 1; mask < (1 << k); ++mask)
    {
        if(__builtin_popcount(mask) == 1) continue;
        for(int i=1;i<=n;++i)
        {
            for(auto &xd: vec[i])
            {
                int u = xd.f;
                int cost = xd.s;
                for(int M = mask; M > 0; M = (M-1)&mask)
                {
                    dp[mask][u] = min(dp[mask][u], dp[M][i] + dp[mask^M][u] + cost);
                }
            }
        }
        Dijkstra(mask);
    }

    int final_mask = (1 << k) - 1;
    int solv = inf;
    for(int i=1;i<=n;++i)
        solv = min(solv, dp[final_mask][i]);
    cout<<solv;
	return 0;
}