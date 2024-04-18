#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

#define ll long long

constexpr int maxn=1e5+7;
constexpr ll inf=6e18+7;

int n;

pair<pair<int,int>,int>p[maxn];

deque<pair<int,int>>x;
deque<pair<int,int>>y;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>p[i].f.f>>p[i].f.s>>p[i].s;
        x.push_back({p[i].f.f-p[i].f.s,p[i].s});
        y.push_back({p[i].f.f+p[i].f.s,p[i].s});
    }

    //find median range
    sort(x.begin(),x.end());
    while(x.size()>=2)
    {
        if(x.front().s<=x.back().s)
        {
            x.back().s-=x.front().s;
            x.pop_front();
        }
        else
        {
            x.front().s-=x.back().s;
            x.pop_back();
        }
    }

    sort(y.begin(),y.end());
    while(y.size()>=2)
    {
        if(y.front().s<=y.back().s)
        {
            y.back().s-=y.front().s;
            y.pop_front();
        }
        else
        {
            y.front().s-=y.back().s;
            y.pop_back();
        }
    }

    int odpx=x.front().f;
    int odpy=y.front().f;

    int solvx=(odpx+odpy)/2;
    int solvy=(odpy-odpx)/2;
    ll odl=inf;

    if(odpx%2 != odpy%2)
    {
        for(int i1=0;i1<=1;++i1)
        for(int i2=0;i2<=1;++i2)
        {
            ll tmp_odl=0;
            for(int i=1;i<=n;++i)
                tmp_odl+=(ll)max(abs((odpx+odpy)/2 + i1 - p[i].f.f),abs((odpy-odpx)/2 + i2 - p[i].f.s))*p[i].s;
            if(tmp_odl<odl)
            {
                odl=tmp_odl;
                solvx=(odpx+odpy)/2 + i1;
                solvy=(odpy-odpx)/2 + i2;
            }
        }
    }

    cout<<solvx<<' '<<solvy;
    return 0;
}