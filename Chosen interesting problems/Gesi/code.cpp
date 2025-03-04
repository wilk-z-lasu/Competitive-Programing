#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>

constexpr int maxn = 1e5+7;
constexpr int inf = 1e18+7;

int n;
pi vec[maxn];

bool check(int x)
{
    int Last = inf;
    for(int i=1; i<=n; i++)
    {
        int New = vec[i].s + x*vec[i].f;
        if(New >= Last) return 0;
        Last = New;
    }
    return 1;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>vec[i].s;
    for(int i=1;i<=n;i++)
        cin>>vec[i].f;

    sort(&vec[1], &vec[n+1], greater<pi>());

    int l = 0, r = 1e9+7;
    while(l<r)
    {
        int mid = (l+r)/2;
        if(check(mid))
            r = mid;
        else
            l = mid+1;
    }
    cout<<l<<'\n';
}