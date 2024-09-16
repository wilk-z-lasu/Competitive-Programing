#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxn = 5e3+7;
constexpr int inf = 1e9+7;

string s1,s2;
int N,M;

int dp[maxn][maxn];//minimal cost when already taken care of elements to [s1 position][s2 position]

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            dp[i][j]=inf;

    cin>>s1>>s2;
    N=s1.size(); s1='#'+s1;
    M=s2.size(); s2='#'+s2;

    dp[0][0]=0;
    for(int i=0; i<=N; i++)
    {
        for(int j=0; j<=M; j++)
        {
            dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
            dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);

            if(s1[i+1] == s2[j+1])
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]);
            else
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+1);

        }
    }
    cout<<dp[N][M];
    return 0;
}