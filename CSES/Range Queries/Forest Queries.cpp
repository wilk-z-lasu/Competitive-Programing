#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=1000+7;

int n,q;
char x;

int dp[maxn][maxn];

int X1,Y1, X2,Y2;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>x;
            if(x=='*')
                dp[i][j]=1;
            dp[i][j]=dp[i][j]+dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
        }
    }
    while(q--)
    {
        cin>>Y1>>X1>>Y2>>X2;
        X1--; Y1--;
        cout<<dp[Y2][X2]-dp[Y2][X1]-dp[Y1][X2]+dp[Y1][X1]<<'\n';
    }
    return 0;
}