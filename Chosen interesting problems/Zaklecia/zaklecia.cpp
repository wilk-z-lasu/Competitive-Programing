//wersja nie dzialajaca
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=3e5+7;
int solv;

int t;
string s;
int n;
//zmienne do manachera
int p[maxn];
int str,r;

vector<int>v[maxn];
set<int>obc;

void manacher()
{
    str=r=0;
    p[0]=0;
    for(int i=1;i<=n-1;i++)
    {
        p[i]=min(p[max(str - (i-str), 0)], r-i);
        p[i]=max(p[i],0);

        int prawo=i+p[i];
        int lewo=i-p[i]+1;

        while(1<=lewo-1 && prawo+1<=n && s[lewo-1]==s[prawo+1])
        {
            lewo--;
            prawo++;
            p[i]++;
        }

        if(i+p[i]>=r)
        {
            str = i;
            r = i+p[i];
        }
    }
}

void clean()
{
    solv=0;
    obc.clear();
    for(int i=0;i<maxn;i++)
        v[i].clear();
    for(int i=0;i<maxn;i++)
        p[i]=0;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    while(t--)
    {
        cin>>s;
        n=s.size();
        s='#'+s;
        manacher();

        for(int i=1;i<=n;i++)
        {
            int prawo=i+p[i];
            if(p[i]!=0) v[prawo].push_back(i+1);//srodek(prawy) i
        }
        for(int i=n+1;i>=1;i--)
        {
            for(auto &u: v[i])
                obc.insert(u);

            int x = (i - p[i]/2 + 1);
            auto it = obc.lower_bound(x);
            if(it!=obc.end() && *it <= i)
                solv=max(solv,(i-*it+1)*4);
        }
        cout<<solv<<'\n';
        clean();
    }
    
    return 0;
}