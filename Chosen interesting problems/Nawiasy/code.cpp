#include <bits/stdc++.h>
using namespace std;
// #define int long long

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

constexpr int maxn=3e4+7;
constexpr int mod = 1e9+9;;

//INPUT DATA
int n;
char w[maxn];

int dp[2][maxn];

int last;
int new_last;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>w[i];

    dp[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        int akt = i&1; int prv = (i-1)&1;
        last = new_last;
        new_last = min(last - 1, n - i);
        for(int wys=0; wys <= new_last; ++wys)
            dp[akt][wys] = dp[prv][wys+1];

        if(w[i]=='(')
        {
            new_last = min(last + 1, n - i);
            for(int wys=1; wys <= new_last; ++wys)
            {
                dp[akt][wys] += dp[prv][wys-1];
                if(dp[akt][wys]>mod)
                    dp[akt][wys]-=mod;
            }
        }
        for(int wys=0; wys<=last; ++wys)
            dp[prv][wys]=0;
    }
    cout<<dp[n&1][0];
    return 0;
}