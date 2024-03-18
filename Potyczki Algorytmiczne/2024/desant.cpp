// Solution for 3/10 pkt //
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=35+7;
constexpr int maxm=1000+7;

int n,m;

int a[maxm];
int b[maxm];

bool solv[maxn];

vector<ll>pos[2];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int it=1;it<=m;++it)
        cin>>a[it]>>b[it];

    for(int k=1;k<=n;++k)
    {
        for(int p=1;p+k-1<=n;++p)
        {
            ll akt=0;
            for(int i=p;i<=p+k-1;++i)
                akt|=(1ll<<i);
            pos[(m+1)&1].push_back(akt);
        }
    }

    for(int i=m;i>=1;--i)
    {
        pos[i&1].clear();
        for(ll &u: pos[(i+1)&1])
        {
            if((u&(1ll<<a[i])) && (u&(1ll<<b[i])))
                pos[i&1].push_back(u);
            else if(!(u&(1ll<<a[i])) && !(u&(1ll<<b[i])))
                pos[i&1].push_back(u);
            else if(!(u&(1ll<<a[i])) && (u&(1ll<<b[i])))
            {
                pos[i&1].push_back(u);
                pos[i&1].push_back(u+(1ll<<a[i])-(1ll<<b[i]));
            }
            // if((u&(1ll<<a[i])) && !(u&(1ll<<b[i])))
            //     //do nothing
        }
    }

    for(ll &u: pos[1])
        solv[__builtin_popcountll(u)]=!solv[__builtin_popcountll(u)];

    for(int i=1;i<=n;++i)
        cout<<solv[i]<<' ';
    return 0;
}