#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

#define float long double

float s,h,v;
int n;
float one;

pair<float,float>klocek[1007];

float sym(float poziom, float l, float density)
{
    float add=0;
    if(density>=one)
        add+=min(l,poziom)*l*l;//od dolu
    else
    {
        add+=min(l*density,poziom)*l*l;//od dolu
        add+=max(poziom-(h-l*(one-density)),(float)0)*l*l;//od gory
    }
    return add/s;
}

bool check(float x)
{
    float rel_poziom=v/s;
    for(int i=1;i<=n;i++)
        rel_poziom+=sym(x,klocek[i].f,klocek[i].s);
    // cout<<rel_poziom<<endl;
    if(rel_poziom>=x)
        return true;
    else
        return false;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    one=1;
    cin>>s>>h>>v;

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>klocek[i].f>>klocek[i].s;

    float l=v/s;
    float r=h;

    while(l<r)//((l*10000)<(r*10000))
    {
        float mid=(l+r+0.0001)/2;
        // cout<<l<<" "<<r<<": "<<mid<<endl;

        if(check(mid))
            l=mid;
        else
            r=mid-0.0001;
    }
    // cout<<l<<" "<<r<<endl;

    cout<<fixed<<setprecision(4)<<l;

    return 0;
}