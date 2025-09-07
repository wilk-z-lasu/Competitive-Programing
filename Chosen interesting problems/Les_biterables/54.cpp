#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 5e5+7;
constexpr int inf = 1e18+7;

int n,d;
int k,p;

int licz(int poz)
{
    return min(poz, d-poz);
}

vector<int>last;
vector<int>vec;

vector<pair<int,bool>>obc;
int sym(int poz)
{
    vector<int>p1;
    vector<int>p2;
    int odp=0;
    for(int i=0;i<=poz;++i)
    {
        odp += obc[i].f;
        if(obc[i].s==0)
            p1.pb(obc[i].f);
        else
            p2.pb(obc[i].f);
    }
    while(!p1.empty() && !p2.empty())
    {
        odp -= 2*min(p1.back(), p2.back());
        p1.pop_back();
        p2.pop_back();
    }
    p1.clear();
    p2.clear();

    for(int i=poz+1;i<sz(obc);++i)
    {
        odp += d-obc[i].f;
        if(obc[i].s==0)
            p1.pb(obc[i].f);
        else
            p2.pb(obc[i].f);
    }
    reverse(p1.begin(), p1.end());
    reverse(p2.begin(), p2.end());
    while(!p1.empty() && !p2.empty())
    {
        odp -= 2*min(d-p1.back(), d-p2.back());
        p1.pop_back();
        p2.pop_back();
    }
    return odp;
}
// void Print(vector<int>& x)
// {
//     for(auto &u: x)
//         cout<<u<<' ';
//     cout<<endl;
// }

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>d;

    for(int iter=1;iter<=n;++iter)
    {
        cin>>k;
        for(int i=1;i<=k;++i)
        {
            cin>>p;
            vec.pb(p);
        }

        if(iter>=2)
        {
            for(auto &u: last)
                obc.pb({u,0});
            for(auto &u: vec)
                obc.pb({u,1});
            sort(obc.begin(), obc.end());

            int solv = inf;
            int ostatnie = 0;
            auto it = vec.begin(); 
            int faza=0;

            for(int i=-1;i<sz(obc);++i)
            {
                if(it!=vec.end() && i>=0 && *it == obc[i].f && obc[i].s==1)
                {
                    if(faza==0)
                    {
                        if(ostatnie > *it)
                            faza=1;
                    }
                    else if(faza==1)
                    {
                        if(ostatnie < *it)
                            return 13;
                    }
                    ostatnie = *it;
                    ++it;
                }
                
                solv = min(solv,sym(i));
            }
            cout<<solv<<'\n';
        }
        last = vec;
        vec.clear();
        obc.clear();
    }
    return 0;
}