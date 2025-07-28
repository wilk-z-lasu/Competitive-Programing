#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()


constexpr int maxn = 10000+7;
constexpr int maxs = 25000+7;
constexpr int maxk = 100+7;

constexpr int inf = 1e18+7;

int n,m,s,k,t;
int a,b,c;
vector<pi>vec[maxn];
map<pi, int>cost;

int l;
int x[maxs];
int y[maxs];
int v;
vector<int>autobus[maxs];

int dp[maxk][maxn];

int sufit(int up, int down)
{
    if(up <= 0) return 0;
    int odp = up/down;
    if((up%down) != 0) ++odp;
    return odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m>>s>>k>>t;
    for(int i=1; i<=m; ++i)
    {
        cin>>a>>b>>c;
        vec[a].pb({b,c});
        vec[b].pb({a,c});
        cost[{a,b}]=c;
        cost[{b,a}]=c;
    }
    for(int i=1; i<=s; ++i)
    {
        cin>>l>>x[i]>>y[i];
        for(int j=1;j<=l;++j)
        {
            cin>>v;
            autobus[i].pb(v);
        }
    }

    for(int i1=0; i1<maxk; ++i1)
        for(int i2=0; i2<maxn; ++i2)
            dp[i1][i2] = inf;

    dp[0][1] = t;
    for(int i=0; i<=k; ++i)
    {
        // cout<<"-----"<<i<<"-----"<<endl;
        for(int j=1; j<=s; ++j)
        {
            int akt = 0;
            int min_start = inf;
            for(int u = 0; u < sz(autobus[j]); ++u)
            {
                int obc = autobus[j][u];
                int nxt = 0;
                if(u+1 < sz(autobus[j]))
                    nxt = autobus[j][u+1];

                // cout<<obc<<" -> "<<nxt<<endl;

                if(dp[i][obc] != inf)
                    min_start = min(min_start, (dp[i][obc] - akt));

                // cout<<"min_start = "<<min_start<<endl;

                if(min_start != inf)
                {
                    int run = sufit(min_start - x[j], y[j]);
                    // cout<<"run = "<<run<<endl;
                    dp[i+1][obc] = min(dp[i+1][obc], x[j] + y[j]*run + akt);
                    // cout<<"dp["<<i+1<<"]["<<obc<<"] = "<<dp[i+1][obc]<<endl; 
                }


                akt += cost[{obc, nxt}];
            }
        }
        for(int j=1; j<=n; ++j)
            dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
    }

    if(dp[k+1][n] == inf)
        cout<<"NIE";
    else
        cout<<dp[k+1][n];
    return 0;
}