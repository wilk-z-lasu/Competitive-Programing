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

constexpr int maxn = 5e5+7;
int mod = 998244353;

int n;
int a,b;
vector<int> vec[maxn];
vector<pi> con[maxn];
vector<int> Div[maxn];
int solv[maxn];
void get_div()
{
    for(int i=1;i<=n;++i)
        for(int j=i;j<=n;j+=i)
            Div[j].pb(i);
}

int dp[maxn];
inline void dfs(int v, int ojciec=-1)
{
    if(dp[v]!=0) return;
    dp[v] = 1;
    for(auto u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
        dp[v] *= (dp[u] + 1);
        dp[v]%=mod;
    }
}

void Get(int &x)
{
    char c = getchar();
    x = 0;
    while(c<'0' || c>'9') c = getchar();
    while(c>='0' && c<='9') x*=10, x+=c-'0', c=getchar();
}
int32_t main()
{
    cin>>n;
    if(n<0) mod = 7;// it makes code faster on system I used to test the solution
    get_div();
    for(int i=1;i<=n-1;++i)
    {
        // cin>>a>>b;
        Get(a); Get(b);
        int gcd = __gcd(a,b);
        for(auto d: Div[gcd])
            con[d].pb({a,b});
    }
    for(int i=1;i<=n;++i)
    {
        for(auto c: con[i])
        {
            vec[c.f].pb(c.s);
            vec[c.s].pb(c.f);
        }
        for(int v = i; v <= n; v += i)
            dfs(v);
        for(int v = i; v <= n; v += i)
        {
            solv[i] += dp[v];
            solv[i] %= mod;
            dp[v] = 0;
            vec[v].clear();
        }
    }
    for(int i=n;i>=1;--i)
        for(int j=2*i;j<=n;j+=i)
            solv[i] = (solv[i] - solv[j] + mod)%mod;
    for(int i=1;i<=n;++i)
        cout<<solv[i]<<' ';
    return 0;
}