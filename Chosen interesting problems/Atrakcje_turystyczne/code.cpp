#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)(A.size())

constexpr int maxn = 8e3+7;
constexpr int mod = 1e9+7;

int n;
char c[maxn];
int dp[2][maxn];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    if(n>=maxn) return 13;
    for(int i=1;i<=n-1;++i)
        cin>>c[i];
    
    dp[1][1]=1;
    for(int i=1;i<=n-1;++i)
    {
        if(c[i]=='<')
        {
            int odp=0;
            for(int j=1;j<=i;++j)
            {
                odp+=dp[i%2][j];
                odp%=mod;
                dp[(i+1)%2][j+1] = odp;
            }
        }
        else
        {
            int odp=0;
            for(int j=i;j>=1;--j)
            {
                odp+=dp[i%2][j];
                odp%=mod;
                dp[(i+1)%2][j] = odp;
            }
        }
        for(int j=1;j<=n;++j)
            dp[i%2][j]=0;
    }
    int solv=0;
    for(int i=1;i<=n;++i)
    {
        solv += dp[n%2][i];
        solv %= mod;
    }
    cout<<solv;
    return 0;
}