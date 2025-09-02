#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) ((int)(A).size())

constexpr int maxn = (1e4 + 7);
constexpr int inf = (1e9 + 7);
constexpr int maxk = 10;
constexpr int maxmask = (1 << 10);

int n,m,d,k;
int a,b,c;

vector<pair<int,vector<int>>>vec[maxn];

vector<pair<pi,vector<int>>>con;

int dp[2][maxmask][maxn];
int solv[maxk];
int dist[maxmask][maxn];

void BFS(int opt, int K)
{
    queue<pi>q;
    for(int i = 0; i < (1<<K); ++i)
        for(int j = 1; j <= n; ++j)
            dist[i][j] = inf;
        
    if(opt==0)
    {
        q.push({0,1});
        dist[0][1] = 0;
    }
    if(opt==1) 
    {
        q.push({0,n});
        dist[0][n] = 0;
    }
    while(!q.empty())
    {
        int mask = q.front().f;
        int v = q.front().s; 
        q.pop();

        for(auto &u: vec[v])
        {
            int tmp_mask = mask;
            for(int i=0;i<K;++i)
                if(u.s[i] >= solv[i])
                    tmp_mask |= (1 << i);
            if(dist[mask][v] + 1 < dist[tmp_mask][u.f])
            {
                dist[tmp_mask][u.f] = dist[mask][v] + 1;
                q.push({tmp_mask,u.f});
            }
            for(int i=0;i<K;++i)
            {
                if(tmp_mask & (1 << i))
                {
                    if(dist[mask][v] + 1 < dist[tmp_mask ^ (1 << i)][u.f])
                    {
                        dist[tmp_mask ^ (1 << i)][u.f] = dist[mask][v] + 1;
                        q.push({tmp_mask ^ (1 << i),u.f});
                    }
                }
            }

        }
    }

    for(int i = 0; i < (1<<K); ++i)
        for(int j = 1; j <= n; ++j)
            dp[opt][i][j] = min(dp[opt][i][j], dist[i][j]);
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

    for(int opt=0; opt<2; ++opt)
        for(int i=0; i<maxmask; ++i)
            for(int j=0; j<maxn; ++j)
                dp[opt][i][j] = inf;

    dp[0][0][1] = 0;
    dp[1][0][n] = 0;

    for(int i=0;i<maxk;++i)
        solv[i] = inf;

    cin>>n>>m>>d>>k;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b;
        vector<int>costs;
        for(int j=0;j<k;++j)
        {
            cin>>c;
            costs.pb(c);
        }
        vec[a].pb({b, costs});
        vec[b].pb({a, costs});
        con.pb({{a,b}, costs});
        con.pb({{b,a}, costs});
    }

    for(int add = 0; add < k; ++add)
    {
        BFS(0, add);
        BFS(1, add);
        int maxi = 0;
        for(int mask = 0; mask < (1<<add); ++mask)
        {
            for(auto &u: con)
            {
                a = u.f.f;
                b = u.f.s;
                vector<int> costs = u.s;

                int needed = 0;
                for(int i=0;i<add;++i)
                    if(costs[i] < solv[i])
                        needed += (1 << i);

                if(dp[0][mask][a] + dp[1][needed ^ (mask & needed)][b] + 1 <= d)
                    maxi = max(maxi, costs[add]);
            }
        }
        solv[add] = maxi;
    }
    for(int i=0;i<k;++i)
        cout<<solv[i]<<' ';
	return 0;
}