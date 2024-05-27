#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e6+7;

int n;
int h[maxn];
int pref[maxn];

pair<int,int> solv(int l, int r, bool turn)
{
    pair<int,int> odp={0,0};
    int s=r-l+1;
    if(s==0)
        return odp;
    else if(s==1)
    {
        if(turn==0) odp.f+=h[r];
        else odp.s+=h[r];
    }
    else if(s==2)
    {
        if(turn==0) odp.f+=h[l]+h[r];
        else odp.s+=h[l]+h[r];
    }
    else if(s%2==1)
    {
        //zjadam co 2
        odp.f=pref[r]-pref[l-2];
        odp.s=pref[r-1]-pref[l-1];
        if(turn) swap(odp.f,odp.s);
    }
    else if(s%2==0)
    {
        pair<int,int> left=solv(l+1,r,!turn);//O(1)
        pair<int,int> right=solv(l,r-1,!turn);//O(1)
        pair<int,int> both = solv(l+1,r-1,!turn);
        if(turn==0)
        {
            left.f+=h[l];
            right.f+=h[r];
            both.f+=h[l]+h[r];
        }
        else
        {
            left.s+=h[l];
            right.s+=h[r];
            both.s+=h[l]+h[r];
        }
        if(turn==0)
            odp=max({left,right,both});
        else
            odp=min({left,right,both});
    }
    return odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=2;i<=n+1;i++)
        cin>>h[i];

    for(int i=2;i<=n+1;i++)
        pref[i] = h[i] + pref[i-2];

    pair<int,int>c=solv(2,n+1,0);
    cout<<c.f<<' '<<c.s;
    return 0;
}