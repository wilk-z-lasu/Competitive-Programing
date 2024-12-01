#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

constexpr int maxn=500007;
int n;

pair<int,int> a[maxn];
int b[maxn];

ll A,B,X,Y;

bool solv[maxn];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i].f;
        a[i].s=i;
    }
    for(int i=1;i<=n;++i)
        cin>>b[i];

    sort(&a[1], &a[n+1], greater<pair<int, int>>());

    for(int i=1;i<=n;++i)
    {
        if(B<=A)
        {
            B+= a[i].f;
            X+=b[a[i].s];
            solv[a[i].s]=1;
        }
        else
        {
            A+=a[i].f;
            Y+=b[a[i].s];
        }
    }
    if(X<Y)
        for(int i=1;i<=n;++i)
            solv[i]=!solv[i];

    for(int i=1;i<=n;++i)
        cout<<solv[i]<<' ';
    return 0;
}