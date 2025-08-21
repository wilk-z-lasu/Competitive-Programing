//solution that gets 20/100 points, but is easily upgradable to 30/100 points
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

struct Cmp {
    bool operator()(const pair<pi,pi>& x1, const pair<pi,pi>& x2) const {
        pi odl1 = x1.f;
        pi odl2 = x2.f;
        pi poz1 = x1.s;
        pi poz2 = x2.s;

        if ((odl1.f * odl2.s) == (odl2.f * odl1.s))
            return (poz1.f * poz2.s) < (poz2.f * poz1.s);
        else
            return (odl1.f * odl2.s) > (odl2.f * odl1.s);
    }
};

set<pair<pi,pi>, Cmp> S;

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
        S.insert({{x[i+1]-x[i],1}, {x[i],1}});

    for(int i=1;i<maxn;++i)
    {
        auto akt = (*S.begin());
        S.erase(akt);
        // cout<<"odl: "<<akt.f.f<<" / "<<akt.f.s<<" poz: "<<akt.s.f<<" / "<<akt.s.s<<endl;

        int new_top = akt.f.f;
        int new_bot = 2*akt.f.s;
        int gcd = __gcd<ll>(new_top, new_bot);
        new_top /= gcd;
        new_bot /= gcd;
        S.insert({{new_top, new_bot}, akt.s});

        int loc_top = akt.s.f * new_bot + new_top * akt.s.s;
        int loc_bot = akt.s.s * new_bot;
        gcd = __gcd<ll>(loc_top, loc_bot);
        loc_top /= gcd;
        loc_bot /= gcd;
        S.insert({{new_top, new_bot}, {loc_top, loc_bot}});

        odp[i] = {loc_top, loc_bot};
    }
    while(z--)
    {
        cin>>k;
        cout<<odp[k].f<<'/'<<odp[k].s<<'\n';
    }
    return 0;
}