#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;
constexpr int maxq=2e5+7;
constexpr int inf=1e9+7;

int n,q;
int a[maxn];
int l,r,m,k;

int get_kratka()
{
    int poz = l+k+m-2;
    if(poz>r) return inf;
    return a[poz];
}
int get_k_th_smallest()
{
    vector<int> v;
    for(int i=l;i<=r;++i)
        v.pb(a[i]);
    sort(v.begin(),v.end());
    if(k-1>=sz(v)) return inf;
    return v[k-1];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;++i)
        cin>>a[i];

    for(int iter=1;iter<=q;++iter)
    {
        cin>>l>>r>>m>>k;
        int solv = get_kratka();
        r=min(r,l+k+m-3);
        solv = min(solv,get_k_th_smallest());
        cout<<solv<<"\n";
    }
    return 0;
}