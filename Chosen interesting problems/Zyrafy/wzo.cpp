#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pi pair<int,int>
#define f first
#define s second
#define pb push_back

constexpr int maxn=1e5+7;

int n;
int tab[maxn];

vector<pi> vec;
int L[maxn], R[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>tab[i];

    vec.pb({0,0});

    for(int i=1;i<=n;i++)
    {
        while(vec.back().f>=tab[i]) vec.pop_back();
        L[i]=vec.back().s+1;
        vec.pb({tab[i],i});
    }

    vec.clear();
    vec.pb({0, n+1});
    for(int i=n;i>=1;i--)
    {
        while(vec.back().f>=tab[i]) vec.pop_back();
        R[i]=vec.back().s-1;
        vec.pb({tab[i],i});
    }

    int solv=0;
    for(int i=1;i<=n;i++)
        solv=max(solv, tab[i]*(R[i]-L[i]+1));
    cout<<solv<<"\n";
    return 0;
}