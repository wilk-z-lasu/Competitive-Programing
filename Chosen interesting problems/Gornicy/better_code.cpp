#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int p=4;
constexpr int inf=1e9+7;

int n;
char x;
int v;

int dp[2][p][p][p][p];

inline int how_many_difrent(int x1, int x2, int x3)
{
    int odp=0;
    for(int i=1;i<=3;i++)
        if(x1==i || x2==i || x3==i)
            odp++;
    return odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for(int i=0;i<=1;i++)
        for(int a=0;a<p;a++)
            for(int b=0;b<p;b++)
                for(int x=0;x<p;x++)
                    for(int y=0;y<p;y++)
                        dp[i][a][b][x][y]=-inf;
    dp[0][0][0][0][0]=0;

    cin>>n;
    for(int i=0;i<=n-1;++i)
    {
        cin>>x;
        if(x=='M')
            v=1;
        if(x=='B')
            v=2;
        if(x=='F')
            v=3;

        for(int a=0;a<p;a++)
            for(int b=0;b<p;b++)
                for(int x=0;x<p;x++)
                    for(int y=0;y<p;y++)
                    {
                        if(dp[i&1][a][b][x][y] != -inf)
                        {
                            dp[(i+1)&1][b][v][x][y] = max(dp[(i+1)&1][b][v][x][y], dp[i&1][a][b][x][y] + how_many_difrent(a,b,v));
                            dp[(i+1)&1][a][b][y][v] = max(dp[(i+1)&1][a][b][y][v], dp[i&1][a][b][x][y] + how_many_difrent(x,y,v));
                        }
                        dp[i&1][a][b][x][y] = -inf;
                    }
    }

    int solv=0;
    for(int a=0;a<p;a++)
        for(int b=0;b<p;b++)
            for(int x=0;x<p;x++)
                for(int y=0;y<p;y++)
                    solv=max(solv,dp[n&1][a][b][x][y]);
    cout<<solv;
    return 0;
}