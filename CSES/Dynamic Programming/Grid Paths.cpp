#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn = 1e3+7;
constexpr int mod = 1e9+7;

int n;
char w;
int tab[maxn][maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>w;
            if(w=='*')
                tab[i][j]=-1;
        }
    }
    if(tab[1][1]!=-1)
        tab[1][1]=1;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(tab[i][j] == -1) continue;
            if(tab[i-1][j] != -1)
                tab[i][j] = (tab[i][j] + tab[i-1][j])%mod;
            if(tab[i][j-1] != -1)
                tab[i][j] = (tab[i][j] + tab[i][j-1])%mod;
        }
    }
    if(tab[n][n]==-1)
        cout<<0;
    else
        cout<<tab[n][n];
    return 0;
}