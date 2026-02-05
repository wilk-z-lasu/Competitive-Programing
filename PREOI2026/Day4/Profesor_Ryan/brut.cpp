#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=5e5+7;
constexpr int mod=1e9+7;

int n;
int a[maxn];
int solv[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];

    vector<pi> vec;
    for(int i=1;i<=n;i++)
    {
        int l = i, r = i;
        while(l-1>=1 && a[l-1]>=a[i]) l--;
        while(r+1<=n && a[r+1]>=a[i]) r++;
        vec.pb({r-l+1, a[i]});
    }
    sort(vec.begin(), vec.end());
    int odp = 0;
    for(int i=n;i>=1;i--)
    {
        while(!vec.empty() && vec.back().f>=i)
        {
            odp = max(odp, vec.back().s);
            vec.pop_back();
        }
        solv[i] = odp;
    }
    for(int i=1;i<=n;i++)
        cout<<solv[i]<<" ";
    return 0;
}