#include<bits/stdc++.h>
using namespace std;
// #define int long long

constexpr int maxn=3000+69;
constexpr int inf=1e9+7;

int n,m;
int A,B,K;
int solv[maxn];

vector<int>vec[maxn];

int siz[maxn];
void licz(int v, int ojciec=0) {
    for(auto u: vec[v])
    {
        if(u==ojciec) continue;
        licz(u,v);
        siz[v]+=siz[u];
    }
    siz[v]++;
}

int dp[maxn][maxn];
void DFS(int v, int ojciec=0) {
    for(auto u: vec[v])
    {
        if(u==ojciec) continue;
        DFS(u,v);
        
        for(int j=siz[v]-siz[u];j>=1;j--)
            for(int k=0;k<=siz[u];k++)
                dp[v][j+k]=min(dp[v][j+k], dp[v][j]+dp[u][k]-2);
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();
    cout.tie();

    for(int i=0;i<maxn;i++)
        solv[i]=inf;
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            dp[i][j]=inf;

    cin>>n;
    for(int i=1;i<n;i++)
    {
        cin>>A>>B;
        vec[A].push_back(B);
        vec[B].push_back(A);
    }

    licz(1);
    
    //jeżyk
    for(int i=1;i<=n;i++)
        dp[i][1]=vec[i].size();

    DFS(1);

    for(int i=1;i<=n;++i)
        for(int k=1;k<=n;++k)
            solv[k] = min(solv[k], dp[i][k]);

    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>K;
        if(solv[K]>=n)
            cout<<"-1\n";
        else
            cout<<solv[K]<<'\n';
    }

    return 0;
}