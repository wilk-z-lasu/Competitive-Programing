#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pi pair<int,int>
#define sz(A) (int)A.size()
#define pb push_back
#define f first
#define s second

constexpr int maxn=2e5+7;

int n;

int dp[maxn][4];
int a,b,c;
vector<pi>vec[maxn];

std::random_device rd;
std::mt19937 g(rd());

constexpr int inf = 1e18;
const int range = 1000;
int dpk[2][2][2*range];//dp for knapsack problem

inline void set_dpk(int siz)
{
    siz = min(siz, range);
    for(int pref = 0; pref < 2; ++pref)
        for(int num_2 = 0; num_2 < 2; ++num_2)
            for(int np = range - siz; np < range+siz; ++np)
                dpk[pref][num_2][np] = -inf;
}

inline void dfs(int v=1, int ojciec=-1, int up = 0)
{
    for(auto &p: vec[v])
        if(p.f!=ojciec)
            dfs(p.f, v, p.s);

    dp[v][0] = 0;
    dp[v][1] = -inf;
    dp[v][2] = -inf;
    dp[v][3] = -inf;

    int i = 0;
    int R = sqrt(sz(vec[v]))+40;
    set_dpk(R);
    dpk[0][0][range] = 0;

    for(auto &p: vec[v])
    {
        int u = p.f;
        if(u==ojciec) continue;
        ++i;

        for(int np = -min(i, R)+1; np < min(i, R); ++np)
        {
            for(int num_2 = 0; num_2 <= 1; ++num_2)
            {
                // use dp[u][0]
                dpk[i%2][num_2][range+np] = max(dpk[i%2][num_2][range+np], dpk[(i-1)%2][num_2][range+np] + dp[u][0]);
                //use dp[u][1]
                dpk[i%2][num_2][range+np+1] = max(dpk[i%2][num_2][range+np+1], dpk[(i-1)%2][num_2][range+np] + dp[u][1]);
                //use dp[u][2]
                dpk[i%2][(num_2+1)%2][range+np] = max(dpk[i%2][(num_2+1)%2][range+np], dpk[(i-1)%2][num_2][range+np] + dp[u][2]);
                // //use dp[u][3]
                dpk[i%2][num_2][range+np-1] = max(dpk[i%2][num_2][range+np-1], dpk[(i-1)%2][num_2][range+np] + dp[u][3]);
            }
        }
    }

    int odp0 = dpk[i%2][0][range];
    int odp1 = dpk[i%2][0][range+1];
    int odp2 = dpk[i%2][1][range];
    int odp3 = dpk[i%2][0][range-1];

    dp[v][0] = odp0;
    if(v==1) return;

    dp[v][0] = max((int)dp[v][0], odp3 + up);
    dp[v][1] = odp0 + up;
    dp[v][2] = odp1 + up;
    dp[v][3] = odp2 + up;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b>>c;
        vec[a].pb({b,c});
        vec[b].pb({a,c});
    }
    
    for(int i=1;i<=n;++i)
        shuffle(vec[i].begin(), vec[i].end(), g);

    set_dpk(inf);
    dfs();
    cout<<dp[1][0];
    return 0;
}