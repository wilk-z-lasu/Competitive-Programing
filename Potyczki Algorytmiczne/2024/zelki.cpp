// Solution for 7/10 pkt //
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=7000+7;
constexpr ll inf=1e18;

int n,k,m;
int kolor,masa,wartosc;

vector<pair<int,int>>colors[maxn];
//u.f- kolor u.s.f-masa u.s.s-cena

vector<pair<int,ll>>vec[maxn];
//.f-nastepny .s-cena

ll solv[maxn];
ll dp[2][maxn];
void prepere()
{
    for(int i=0;i<maxn;++i)
    solv[i]=inf;
}

bool vis[maxn];
void Dijkstra()
{
    priority_queue<pair<ll,int>>pq;
    //.f=-cena .s=miejsce
    pq.push({0,0});

    while(!pq.empty())
    {
        auto top=pq.top();
        pq.pop();
        top.f=-top.f;

        if(vis[top.s]) continue;
        vis[top.s]=true;
        solv[top.s]=top.f;
        for(auto &u: vec[top.s])
        {
            if(!vis[u.f])
            {
                // cout<<"-> "<<u.f<<endl;
                pq.push({-(top.f+u.s),u.f});
            }
        }

    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>k>>m;
    for(int i=1;i<=n;++i)
    {
        cin>>kolor>>masa>>wartosc;
        colors[kolor].push_back({masa,wartosc});
    }

    prepere();
    dp[0][0]=0;
    for(int i=1;i<=m-1;++i)
        dp[0][i]=inf;
    for(int kol=1;kol<=k;++kol)
    {
        for(int i=0;i<=m-1;++i)
            dp[kol&1][i]=inf;
        for(auto &v: colors[kol])
            for(int i=0;i<=m-1;i++)
                dp[kol&1][(i+v.f)%m] = min(dp[(kol-1)&1][i]+v.s, dp[kol&1][(i+v.f)%m]);
    }
    // dp[k] <- mam zapisany najmniejszy koszt sciezki danej dlugosci

    // for(int i=0;i<=m-1;i++)
    //     cout<<dp[k][i]<<' ';
    // cout<<endl;

    for(int i=0;i<=m-1;++i)
        for(int j=1;j<=m-1;++j)
            if(dp[k&1][j]<inf)
            {
                // cout<<i<<" -> "<<(i+j)%m<<": "<<dp[k][j]<<endl;
                vec[i].push_back({(i+j)%m,dp[k&1][j]});
            }

    Dijkstra();
    for(int i=0;i<=m-1;++i)
    {
        if(solv[i]==inf)
            cout<<"-1\n";
        else
            cout<<solv[i]<<'\n';
    }
    return 0;
}