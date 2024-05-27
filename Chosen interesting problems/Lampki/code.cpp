#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=407;
int n,m;
char tab[maxn][maxn];
int change_y[maxn];
int change_x[maxn];

int odp;

void solv(int x, int y)
{
    bool pole=0;
    if(tab[y][x]=='1') pole=1;

    pole^=change_x[x];
    pole^=change_y[y];

    if(!pole)
    {
        odp++;
        change_y[y]^=1;
        change_x[x]^=1;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>tab[i][j];

    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            solv(j,i);

    cout<<odp;
    return 0;
}