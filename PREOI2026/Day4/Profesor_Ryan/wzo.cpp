#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=5e5+7;
constexpr int inf=1e9+7;

int n;
int a[maxn];
int solv[maxn];
int l[maxn];
int r[maxn];

vector<int> vec[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];

    for(int i=1;i<=n;++i)
    {
        l[i] = 1;
        r[i] = n;
    }

    vector<int> S;
    for(int i=1;i<=n;++i)
    {
        while(!S.empty() && a[S.back()]>a[i])
        {
            r[S.back()] = i-1;
            S.pop_back();
        }
        S.push_back(i);
    }
    S.clear();
    for(int i=n;i>=1;--i)
    {
        while(!S.empty() && a[S.back()]>a[i])
        {
            l[S.back()] = i+1;
            S.pop_back();
        }
        S.push_back(i);
    }

    for(int i=1;i<=n;i++)
        vec[r[i]-l[i]+1].pb(a[i]);
    
    int odp = 0;
    for(int i=n;i>=1;i--)
    {
        for(auto &u: vec[i])
            odp = max(odp, u);
        solv[i] = odp;
    }
    for(int i=1;i<=n;i++)
        cout<<solv[i]<<" ";
    return 0;
}