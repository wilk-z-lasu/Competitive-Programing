#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second

constexpr int maxn=507;
constexpr int mod = 998244353;

int n,k;
int tab[maxn][maxn];
int dp[maxn][maxn][300];

int idx;
int Div[300];
int nwd[300][300];

map<int,bool>divs;
unordered_map<int,int>m;
void cnt_Div()
{
    for(int i=1;i*i<=k;i++)
    {
        if(k%i==0)
        {
            divs[i]=1;
            divs[k/i]=1;
        }
    }
    for(auto &u: divs)
    {
        Div[++idx] = u.f;
        m[u.f] = idx;
    }
    for(int i=1;i<=idx;i++)
        for(int j=1;j<=idx;j++)
            nwd[i][j] = m[__gcd<ll>((ll)Div[i] * (ll)Div[j], (ll)k)];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>tab[i][j];
            if(tab[i][j]!=-1)
                tab[i][j] = __gcd(tab[i][j], k);
        }
    }

    cnt_Div();

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            tab[i][j] = m[tab[i][j]];

    if(tab[1][1]!=-1) 
        dp[1][1][tab[1][1]]=1;
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[i][j]==-1) continue;
            for(int x=1;x<=idx;x++)
            {
                if(i+1<=n && tab[i+1][j]!=-1)
                {
                    int des = nwd[tab[i+1][j]][x];
                    
                    dp[i+1][j][des] = dp[i+1][j][des] + dp[i][j][x];
                    if(dp[i+1][j][des]>=mod)
                        dp[i+1][j][des]-=mod;
                }
                if(j+1<=n && tab[i][j+1]!=-1)
                {
                    int des = nwd[tab[i][j+1]][x];

                    dp[i][j+1][des] = dp[i][j+1][des] + dp[i][j][x];
                    if(dp[i][j+1][des]>=mod)
                        dp[i][j+1][des]-=mod;
                }
            }
        }
    }
    cout<<dp[n][n][idx];
    return 0;
}