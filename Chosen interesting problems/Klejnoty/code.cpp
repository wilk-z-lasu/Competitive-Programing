#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=10000+7;
constexpr int inf=1e9+7;

int n;
int a,b;
vector<int>vec[maxn];

int dp[maxn][107];
int dp_pref[maxn][107];
int dp_suf[maxn][107];


void dfs(int v=1, int ojciec=-1)
{
    for(int kolor=1;kolor<=100;kolor++)
        dp[v][kolor]=kolor;
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
        for(int kolor=1;kolor<=100;kolor++)
            dp[v][kolor]+=min(dp_pref[u][kolor-1],dp_suf[u][kolor+1]);
    }

    dp_pref[v][0]=inf;
    for(int kolor=1;kolor<=100;kolor++)
        dp_pref[v][kolor] = min(dp[v][kolor], dp_pref[v][kolor-1]);
    dp_suf[v][101]=inf;
    for(int kolor=100;kolor>=1;kolor--)
        dp_suf[v][kolor] = min(dp[v][kolor], dp_suf[v][kolor+1]);

}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    dfs();
    cout<<dp_pref[1][100];
    return 0;
}