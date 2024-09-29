#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int maxn=10000+7;
constexpr int inf=1e9+7;

int n,l;
int tab[maxn];
int q;
pair<int,int> zap[maxn];

int it=1;
int nearest_zap[maxn];

int dif[maxn];
int solv[101][maxn];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>l;
    for(int i=1;i<=n;i++)
        cin>>tab[i];
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        cin>>zap[i].f;
        zap[i].s=i;
    }

    sort(&zap[1], &zap[q+1]);
    zap[n+1].f=inf;
    for(int i=0;i<=n;i++)
    {
        while(zap[it].f<i)
            it++;
        nearest_zap[i]=zap[it].s;
    }
    for(int x=1;x<=n;x++)
    {
        for(int i=0;i<=n;i++)
            dif[i]=0;
        for(int i=1;i+x<=n;i++)
            if(tab[i]!=tab[i+x])
                dif[i]=1;
        for(int i=1;i<=n;i++)
            dif[i]+=dif[i-1];

        for(int i=1;i<=n-l+1-x;i++)
        {
            solv[nearest_zap[(dif[i+l-1]-dif[i-1])]][i]++;
            solv[nearest_zap[(dif[i+l-1]-dif[i-1])]][i+x]++;
        }
    }

    for(int i=2;i<=q;i++)
        for(int j=1;j<=n;j++)
            solv[zap[i].s][j]+=solv[zap[i-1].s][j];

    for(int i=1;i<=q;i++)
    {
        for(int j=1;j+l-1<=n;j++)
            cout<<solv[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}