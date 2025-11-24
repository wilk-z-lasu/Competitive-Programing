#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int unsigned long long

int d;
int n;
int x;
int p;

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>d;
    for(int iter=1;iter<=d;iter++)
    {
        cin>>n;
        cin>>x;
        cin>>p;
        p/=__gcd((unsigned)p,(unsigned)x);
        for(int i=3;i<=n;i++)
        {
            cin>>x;
            p/=__gcd((unsigned)p,(unsigned)x);
        }
        if(p==1)
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }

    return 0;
}