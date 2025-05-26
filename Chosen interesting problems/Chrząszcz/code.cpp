#include<bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 300+7;

int n,m;

int x[maxn];

int start=1;
int dp[maxn][maxn][2];
int odp=0;
void f(int k)
{
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            for(int p=0;p<=1;++p)
                dp[i][j][p]=0;

    dp[start][start][0]=dp[start][start][1]=k*m;
    for(int i=start;i>=1;--i)
    {
        for(int j=start;j<=n;++j)
        {
            for(int p=0;p<=1;++p)
            {
                int used = j-i+1;
                int left = k - used;
                
                if(used == k)
                {
                    // cout<<dp[i][j][p]<<" <- "<<i<<" "<<j<<" "<<p<<endl;
                    odp = max(odp, dp[i][j][p]);
                }
                else 
                {
                    if(j+1<=n)
                    {
                        if(p==0)
                            dp[i][j+1][1] = max(dp[i][j+1][1], dp[i][j][p] - left*abs(x[j+1]-x[i]));
                        if(p==1)
                            dp[i][j+1][1] = max(dp[i][j+1][1], dp[i][j][p] - left*abs(x[j+1]-x[j]));
                    }
                    if(i-1>=1)
                    {
                        if(p==0)
                            dp[i-1][j][0] = max(dp[i-1][j][0], dp[i][j][p] - left*abs(x[i]-x[i-1]));
                        if(p==1)
                            dp[i-1][j][0] = max(dp[i-1][j][0], dp[i][j][p] - left*abs(x[j]-x[i-1]));
                    }
                }
            }
        }
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    cin>>n>>m;

    bool have_zero=0;
    for(int i=1;i<=n;++i)
    {
        cin>>x[i];
        if(x[i]==0)
            have_zero=1;
    }
    if(!have_zero)
    {
        n++; 
        x[n] = 0;
    }

    sort(&x[1], &x[n+1]);

    while(x[start]!=0)
        ++start;

    for(int i=1;i<=n;++i)
    {
        // cout<<"----"<<i<<"----"<<endl;
        f(i);
    }

    if(!have_zero) odp-=m;

    cout<<odp;
    return 0;
}