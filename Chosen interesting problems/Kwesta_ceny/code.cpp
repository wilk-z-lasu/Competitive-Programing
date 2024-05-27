#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=200000+7;

int n,k;
int a,b;

vector<int>vec[maxn];

int dp[maxn];
int nr[maxn];

void licz_dp(int v, int ojciec=0)
{
    dp[v]=0;
    for(auto &u: vec[v])
    {
        if(u==ojciec || nr[u]) continue;
        licz_dp(u,v);
        dp[v]+=dp[u];
    }
    dp[v]++;
}

int find_centroid(int s, int v=1, int ojciec=0)
{
    for(auto &u: vec[v])
    {
        if(u==ojciec || nr[u]) continue;
        if(dp[u]>s/2) return find_centroid(s, u, v);
    }
    return v;
}

void rozbij(int s, int v, int l)
{
    nr[v]=l;
    licz_dp(v);
    for(auto &u: vec[v])
    {
        if(nr[u]) continue;
        int cen = find_centroid(dp[u], u, v);
        nr[cen]=l;
        rozbij(dp[u],cen,l+1);
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k;

    for(int i=1;i<=n-1;i++)
    {
        cin>>a>>b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    licz_dp(1);
    int cen=find_centroid(n,1);
    rozbij(n, cen, 1);

    for(int i=1;i<=n;i++)
        cout<<nr[i]<<' ';

    return 0;
}