#include <bits/stdc++.h>
using namespace std;

constexpr int maxn=107;
constexpr int inf=1e9;

int n;
char x;
int w[maxn][maxn];

int vec[maxn][maxn];

map<int,bool>solv;

int get(int v, int odl)
{
    return (v+odl)/(n+1)+(v+odl)%(n+1);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>x;
            if(x=='1')
                w[i][j]=1;
        }
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            vec[i][j]=0;

    for(int i=1;i<=n;i++)
        vec[i][get(i,1)]=1;

    for(int u=1;u<=n;u++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(vec[i][u] && vec[u][j] && (w[i][u] || !w[u][j]))
                    vec[i][j]=1;

    for(int u=2;u<=n;u++)//oddalenie
        for(int i=1;i<=n;i++)
            for(int j=1;j<=u-1;j++)//odleglosc srodkowego od i
                if(vec[i][get(i,j)] && vec[get(i,j)][get(i,u)] && (w[i][get(i,j)] || !w[get(i,j)][get(i,u)]))
                    vec[i][get(i,u)]=1;

    for(int v1=1;v1<=n;v1++)
        for(int v2=1;v2<=n;v2++)
            if(w[v1][v2] && vec[v1][v2] && vec[v2][v1])
                solv[v1]=1;

    cout<<solv.size()<<'\n';
    for(auto &u: solv)
        cout<<u.first<<'\n';

    return 0;
}