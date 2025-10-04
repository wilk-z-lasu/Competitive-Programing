//wzorcowka na zagubione wydruki - rozwiazanie ostateczne
//Mateusz Woloszyk
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int inf=1000000007;

int n,m,p,t;
int x;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    vector<int>tab(n+1);
    vector<pi>Last(n+1);

    for(int i=1;i<=n;++i)
        cin>>tab[i];
    cin>>m; m = min(m,n);
    cin>>t;
    cin>>p;

    tab[0]=0;
    sort(&tab[1], &tab[n+1]);

    int it=1;
    for(int i=1;i<=n;++i)
    {
        while(tab[i]-tab[it] > t)
            it++;
        Last[i] = {it, i-it+1};
    }

    vector<vector<pair<int,pair<int,bool>>>>dp(n+1, vector<pair<int,pair<int,bool>>>(m+1));
    for(int i=0;i<=n;++i)
    {
        dp[i][0] = {0,{0,0}};
        for(int j=1;j<=m;++j)
            dp[i][j] = {-inf,{0,0}};
    }

    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=min(m, i);++j)
        {
            if(dp[i-1][j].f != -inf) dp[i][j] = max(dp[i][j], {dp[i-1][j].f, {i-1,0}});
            if(j-1>=0 && dp[Last[i].f-1][j-1].f != -inf) dp[i][j] = max(dp[i][j], {dp[Last[i].f-1][j-1].f+Last[i].s, {Last[i].f-1,1}});
        }
    }

    pair<int,pair<int,int>>solv={0,{0,0}};
    for(int i=1;i<=n;++i)
        for(int j=0;j<=min(m, i);++j)
            solv = max(solv, {dp[i][j].f,{-i,-j}});
    cout<<solv.f<<' '<<tab[-solv.s.f]<<' '<<-solv.s.s<<'\n';

    if(p==1 && m>0)
    {
        int akt_v = -solv.s.f;//actual position in tab
        int akt_com = -solv.s.s;//actual number of compartments

        vector<int>odp;
        while(akt_v!=0)
        {
            int akt_start = dp[akt_v][akt_com].s.f;

            if(akt_v == -solv.s.f)
                odp.pb(tab[akt_v]-tab[akt_start+1]);
            else
                odp.pb(tab[akt_v+1]-tab[akt_start+1]);

            if(dp[akt_v][akt_com].s.s)
            {
                odp.pb(-1);
                akt_com --;
            }

            akt_v = akt_start;
        }
        if(tab[1]!=0) odp.pb(tab[1]);
        reverse(odp.begin(), odp.end());
       
        //WYPISYWANIE WYNIKU
        int akt_range=0;
        for(int e: odp)
        {
            if(e==-1)
            {
                if(akt_range>0) cout<<"R "<<akt_range<<' ';
                akt_range=0;
                cout<<"M ";
            }
            else
                akt_range+=e;
        }
        if(akt_range>0) cout<<"R "<<akt_range<<' ';
    }
    return 0;
}