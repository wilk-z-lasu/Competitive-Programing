#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
 
constexpr int maxn=21;
constexpr int inf=1e13+7;

int n;
int a[2][maxn];

int z;
string w;
int k;
int q;

int maska;

pair<int,int> dp[maxn][1<<(maxn-1)];

pair<int,int> merge(pair<int,int>akt, pair<int,int>nowe)
{
    if(nowe.f>akt.f)
        return nowe;
    if(nowe.f<akt.f)
        return akt;
    // if(nowe.f==akt.f)
    return {akt.f,akt.s+nowe.s};
}

int is_set(int m, int l)
{
    if (m & (1 << l))
        return 1;
    else
        return 0;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[0][i];
    for(int i=1;i<=n;i++)
        cin>>a[1][i];


    for(int i=0;i<=n;i++)
        for(int j=0;j<(1<<n);j++)
            dp[i][j].f=-inf;

    cin>>z;
    for(int i=1;i<=z;i++)
    {
        cin>>w>>k;
        maska=0;
        for(int j=0;j<w.size();j++)
            if(w[j]=='1')
                maska|=(1<<j);
        dp[0][maska]=merge(dp[0][maska],{-k,1});
        // cout<<"dp[0]["<<maska<<"] = {"<<dp[0][maska].f<<", "<<dp[0][maska].s<<"}"<<endl;
    }

    for(int i=0;i<=n-1;i++)
    {
        for(int j=0;j<(1<<n);j++)
        {
            //rozpatruje ze maska przewiduje dobrze nastepny mecz
            dp[i+1][j]=merge(dp[i+1][j], {dp[i][j].f+a[is_set(j,i)][i+1],dp[i][j].s});
            // //rozpatruje ze nastepny mecz wydzarzy sie inaczej
            dp[i+1][j^(1<<i)]=merge(dp[i+1][j^(1<<i)], dp[i][j]);
        }
    }

    cin>>q;
    while(q--)
    {
        cin>>w;
        maska=0;
        for(int j=0;j<w.size();j++)
            if(w[j]=='1')
                maska|=(1<<j);
        cout<<dp[n][maska].f<<' '<<dp[n][maska].s<<'\n';
    }

    return 0;
}