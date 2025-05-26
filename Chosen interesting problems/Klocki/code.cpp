#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define f first
#define s second

int klocek[100];

short plecak[1000007];

short plecak_new[1000007];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    plecak[0]=0;
    for(int i=1;i<1000007;++i) 
        plecak[i]=100;

    plecak_new[0]=0;
    for(int i=1;i<1000007;++i) 
        plecak_new[i]=100;

    int n,k,s; cin>>n>>k>>s;

    for(int i=0;i<n;++i)
        cin>>klocek[i];

    for(int iter=0;iter<n;++iter)
    {
        for(int i=klocek[iter];i<=s;++i)
            plecak_new[i] = plecak[i-klocek[iter]]+1;
        for(int i=0;i<=s;++i)
            if(plecak_new[i]<plecak[i]) 
                plecak[i]=plecak_new[i];
    }

    int odp=0;
    for(int i=0;i<=s;++i)
        if(plecak[i]<=k) odp=i;
    cout<<odp;
    return 0;
}