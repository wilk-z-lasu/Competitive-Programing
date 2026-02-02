#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int maxm=4e5+7;
constexpr int mod=1e9+7;

int n,m;
int a[maxm],b[maxm],w[maxm];

int rep[maxn];
void prepare()
{
    for(int i=1;i<=n;++i)
        rep[i]=i;
}
int Find(int x)
{
    if(x==rep[x]) return x;
    else return rep[x] = Find(rep[x]);
}
void Union(int A, int B)
{
    A = Find(A);
    B = Find(B);
    rep[A] = B;
}

vector<pair<int,pi>> List;
int min_odp = 0;

int check_mask(int mask)
{
    if(__builtin_popcount(mask) != n-1) return 0;
    prepare();
    int curr_odp = 0;
    for(int i=0; i<m; ++i)
    {
        if(mask & (1LL<<i))
        {
            int W = List[i].f;
            int A = List[i].s.f;
            int B = List[i].s.s;
            if(Find(A)==Find(B)) return 0;

            Union(A,B);
            curr_odp += W;
        }
    }
    if(curr_odp == min_odp)
        return 1;
    else
        return 0;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    for(int i=0;i<m;++i)
    {
        cin>>a[i]>>b[i]>>w[i];
        if(a[i]>b[i]) swap(a[i],b[i]);
        List.pb({w[i], {a[i],b[i]}});
    }

    sort(List.begin(),List.end());
    prepare();
    for(int i=0;i<m;++i)
    {
        int W = List[i].f;
        int A = List[i].s.f;
        int B = List[i].s.s;
        if(Find(A) != Find(B))
        {
            Union(A,B);
            min_odp+=W;
        }
    }

    int solv = 0;
    for(int mask = 0; mask < (1LL<<m); ++mask)
    {
        solv += check_mask(mask);
        solv %= mod;
    }
    cout<<solv;
    return 0;
}