#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=2e5+7;

int n,q;
int pref[maxn];

int a,b;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>pref[i];
        pref[i]+=pref[i-1];
    }
    while(q--)
    {
        cin>>a>>b;
        cout<<pref[b]-pref[a-1]<<'\n';
    }
    return 0;
}