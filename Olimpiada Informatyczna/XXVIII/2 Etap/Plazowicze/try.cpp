//solution that gets 80/100 points
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 1e6+7;

int n,X,z,k;
int x[maxn];
vector<pi> zap;

struct Cmp {
    bool operator()(const pair<pair<pi,int>,int>& x1, const pair<pair<pi,int>,int>& x2) const {
        pi odl1 = x1.f.f;
        pi odl2 = x2.f.f;
        int poz1 = x1.f.s;
        int poz2 = x2.f.s;

        if ((odl1.f * odl2.s) == (odl2.f * odl1.s))
            return (poz1 < poz2);
        else
            return (odl1.f * odl2.s) > (odl2.f * odl1.s);
    }
};

set<pair<pair<pi,int>,int>, Cmp> S;

pi odp[maxn];

int32_t main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>X>>z;
    for(int i=1;i<=n;++i)
        cin>>x[i];
    
    for(int i=1;i<=n-1;++i)
        S.insert({{{x[i+1]-x[i],1}, x[i]}, {1}});

    for(int i=1;i<=z;++i)
    {
        cin>>k;
        zap.pb({k, i});
    }
    sort(zap.begin(), zap.end(), greater<pi>());

    int Prev=0;
    while(!zap.empty())
    {
        auto akt = (*S.begin());
        S.erase(akt);

        // cout<<akt.f.f.f<<" / "<<akt.f.f.s<<" poz: "<<akt.f.s<<" ile: "<<akt.s<<endl;
        
        int new_top = akt.f.f.f;
        int new_bot = 2*akt.f.f.s;
        int gcd = __gcd<ll>(new_top, new_bot);
        new_top /= gcd;
        new_bot /= gcd;
        S.insert({{{new_top, new_bot}, akt.f.s}, 2*akt.s});
        
        while(!zap.empty() && zap.back().f <= Prev + akt.s)
        {
            // odp[zap.back().s] = 
            // akt.f.s + (new_top / new_bot)*(Prev + akt.s - zap.back().f + 1)
            // cout<<akt.f.s<<" + ("<<new_top<<" / "<<new_bot<<") + ("<<akt.f.f.f<<" / "<<akt.f.f.s<<") * "<<(zap.back().f - Prev - 1)<<endl;
            pair<__int128, __int128> solv = {akt.f.s,(__int128)1};

            solv.f = solv.f*new_bot + new_top;
            solv.s = solv.s * new_bot;
            
            gcd = __gcd<__int128>(solv.f, solv.s);
            solv.f /= gcd;
            solv.s /= gcd;
            
            solv.f = solv.f*akt.f.f.s + akt.f.f.f*(zap.back().f - Prev - 1)*solv.s;
            solv.s = solv.s * akt.f.f.s;
            
            gcd = __gcd<__int128>(solv.f, solv.s);
            solv.f /= gcd;
            solv.s /= gcd;
            
            odp[zap.back().s] = solv;
            zap.pop_back();
        }
        Prev += akt.s;
    }

    for(int i=1;i<=z;++i)
        cout<<odp[i].f<<'/'<<odp[i].s<<endl;
    
    return 0;
}