#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e5+7;
int n;
int x,x1,x2;
int solv[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    if(n==1)
    {
        cin>>x1;
        cout<<x1;
        return 0;
    }
    cin>>x1>>x2;
    solv[1] = solv[2] = x2;
    for(int i=3;i<=n;i++)
    {
        cin>>x;
        solv[i] = min(solv[i-1] + x1 + x, solv[i-2] + x1 + x + x2 + x2); 
    }
    cout<<solv[n];
    return 0;
}