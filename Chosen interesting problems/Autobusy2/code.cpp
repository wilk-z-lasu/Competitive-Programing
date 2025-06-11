#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

constexpr int inf=1e9+7;
constexpr int maxm=1007;

int t1,t2,m,n1,n2;
int x;
vector<int>tab[maxm];

int min_sufix[1000000+7];

int solv=inf;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t1>>t2>>m>>n1>>n2;

    for(int i=1;i<=m;i++)
    {
        tab[i].push_back(0);//indeksowanie od 1
        for(int j=1;j<=n1;j++)
        {
            cin>>x;
            tab[i].push_back(x);
        }
        for(int j=1;j<=n2;j++)
        {
            cin>>x;
            tab[i].push_back(x);
        }
    }
    for(int p=2;p<=m;p++)//przystanek
    {
        vector<pair<int,int>>lewo;//.f-czas dojazdu
        vector<pair<int,int>>prawo;//.f-czas odjazdu

        for(int j=1;j<=n1;j++)
            if(tab[1][j]-t1>=0)
                lewo.push_back({tab[p][j],tab[1][j]-t1});
        for(int j=n1+1;j<=n1+n2;j++)
            if(t2-tab[1][j]>=0)
                prawo.push_back({tab[p][j],t2-tab[1][j]});

        sort(lewo.begin(),lewo.end());
        sort(prawo.begin(),prawo.end());

        min_sufix[prawo.size()]=inf;
        for(int i=prawo.size()-1;i>=0;i--)
            min_sufix[i]=min(prawo[i].f+prawo[i].s,min_sufix[i+1]);

        int j=0;
        for(int i=0;i<lewo.size();i++)
        {
            for(;j<prawo.size();j++)
            {
                if(lewo[i].f<=prawo[j].f)
                {
                    solv=min(solv,lewo[i].s+min_sufix[j]-lewo[i].f);
                    break;
                }
            }
        }
    }
    solv=min(solv,t2-t1);
    cout<<solv;

    return 0;
}