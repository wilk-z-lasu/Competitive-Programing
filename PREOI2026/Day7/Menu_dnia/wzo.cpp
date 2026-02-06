#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

pair<pi,pi> maxi = {{0,0},{0,0}};//.f.f = first maximum ending A .f.s=odp[A] .s.f = second maximum ending A .s.s=odp[A]

int n,m;
int A,W;

void Fastin(int &x)
{
    x=0;
    char c=getchar();
    bool minus=false;
    while(c!='-' && (c<'0' || c>'9')) c=getchar();
    if(c=='-')
    {
        minus=true;
        c=getchar();
    }
    while(c>='0' && c<='9')
    {
        x=x*10+(c-'0');
        c=getchar();
    }
    if(minus) x = -x;
}

int32_t main()
{
    Fastin(n);
    Fastin(m);
    for(int i=1;i<=n;++i)
    {
        Fastin(A);
        Fastin(W);
        if(A == maxi.f.f)
            maxi.f.s = max(maxi.f.s, maxi.s.s + W);
        else
        {
            pi prep = {A, max(maxi.f.s + W, 0ll)};
            if(prep.s >= maxi.f.s)
            {
                maxi.s = maxi.f;
                maxi.f = prep;
            }
            else if(prep.s > maxi.s.s)
                maxi.s = prep;
        }
    }
    cout<<maxi.f.s<<"\n";
    return 0;
}