#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2000+7;
constexpr int mod=1e9;

int combi[maxn];

int F(int x)
{
    return (combi[x]-combi[x-1]+mod)%mod;
}

int t;
int n;
pair<int,int>vec[maxn];
int dp[maxn];

int dfs(int v=1)
{
    if(v==0) return 0;

    int l=vec[v].f;
    int r=vec[v].s;

    if(l==0 && r==0)
    {
        dp[v]=0;
        return 1;
    }

    int H1=dfs(l);
    int H2=dfs(r);
    int H=max(H1, H2)+1;

    if(l==0)
    {
        dp[v]=dp[r];
        return H;
    }
    if(r==0)
    {
        dp[v] = ((combi[H1-1])*F(H1) + dp[l]*(combi[H1]) + 1*(dp[r]))%mod;
        return H;
    }
    
    if(H1<H2)
        dp[v] = ((combi[H1-1])*F(H2) + dp[l]*F(H2) + 1*dp[r])%mod;
    if(H1>H2)
        dp[v] = ((combi[H1-1])*F(H1) + dp[l]*(combi[H1]) + 1*(dp[r] + (combi[H2-1])))%mod;
    if(H1==H2)
        dp[v] = ((combi[H1-1])*F(H2) + dp[l]*(combi[H1]) + 1*(dp[r] + (combi[H2-1])))%mod;

    // cout<<"dp["<<v<<"]: "<<dp[v]<<endl;

    return H;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    combi[0]=1;
    for(int i=1;i<maxn;i++)
        combi[i]=((combi[i-1]*combi[i-1])+1)%mod;

    cin>>t;
    for(int iter=1;iter<=t;iter++)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>vec[i].f>>vec[i].s;
            if(vec[i].f==-1) vec[i].f=0;
            if(vec[i].s==-1) vec[i].s=0;
        }
        int h=dfs();
        cout<<(dp[1]+combi[h-1])%mod<<'\n';

        for(int i=1;i<=n;i++)
            vec[i].f=vec[i].s=dp[i]=0;
    }
    return 0;
}

/*
1
6
4 2
3 -1
5 -1
-1 6
-1 -1
-1 -1
*/