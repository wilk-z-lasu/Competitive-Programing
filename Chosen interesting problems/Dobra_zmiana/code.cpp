#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int mod=998244353;

int t;
int w,g,l;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    while(t--)
    {
        cin>>w>>g>>l;
        cout<<(((w%mod-g%mod+mod)%mod)*((2*l+1)%mod))%mod<<'\n';
    }
    
    return 0;
}