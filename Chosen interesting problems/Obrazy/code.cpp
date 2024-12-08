#include <bits/stdc++.h>
using namespace std;
#define int long long

int h,w;
int n;
int d[33];

int ile_h[33];
int ile_w[33];

int solv;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>h>>w;
    cin>>n;

    for(int i=1;i<=n;i++)
        cin>>d[i];

    if(h%d[1]!=0 || w%d[1]!=0)
    {
        cout<<-1;
        return 0;
    }

    ile_h[1]=(h/d[1]);
    ile_w[1]=(w/d[1]);
    solv+=ile_w[1]*ile_h[1];

    for(int i=2;i<=n;++i)
    {
        int need=(d[i]/d[i-1]);
        // int mini=min((ile_h[i-1]/need),(ile_w[i-1]/need));
        ile_h[i]= ile_h[i-1]/need;
        ile_w[i]= ile_w[i-1]/need;
        solv+=ile_w[i]*ile_h[i];

        solv-=(ile_h[i]*need)*(ile_w[i]*need);
    }

    cout<<solv;
    return 0;
}