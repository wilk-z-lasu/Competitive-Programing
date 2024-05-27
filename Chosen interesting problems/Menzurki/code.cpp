#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

#pragma GCC target("avx,avx2,fma,tune=native")
#pragma GCC optimization("Ofast,unroll-loops")

constexpr ll maxn=1e5;
constexpr int inf=1e9+7;

ll n;
ll l;
ll x[25];

int dp[25][maxn];

queue<pair<ll,ll>>q;

void bfs()
{
    while(!q.empty())
    {
        ll v1=q.front().f;
        ll v2=q.front().s;
        q.pop();

        if(v1==l || x[v2]==l)
        {
            cout<<dp[v2][v1];
            exit(0);
        }

        dp[v2][v1]++;
        for(ll i=n;i>=0;--i)
        {
            if(dp[v2][x[i]]==inf)//zmiana poziomu pierwszej menzurki
            {
                dp[v2][x[i]]=dp[v2][v1];
                q.push({x[i],v2});
            }
            if(dp[i][v1]==inf)//zmiana poziomu drogiej menzurki
            {
                dp[i][v1]=dp[v2][v1];
                q.push({v1,i});
            }
            if(0<=v1+x[v2]-x[i] && v1+x[v2]-x[i]<maxn && dp[i][v1+x[v2]-x[i]]==inf)
            {
                dp[i][v1+x[v2]-x[i]]=dp[v2][v1];
                q.push({v1+x[v2]-x[i],i});
            }
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n; --n;
    for(ll i=0;i<=n;++i)
        cin>>x[i];
    cin>>l;

    for(ll j=0;j<=n;++j)
        for(ll i=0;i<maxn;++i)
            dp[j][i]=inf;

    dp[0][0]=0;
    q.push({0,0});
    bfs();

    cout<<"NIE";
    return 0;
}