#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=21;
int n;
int tab[maxn];

vector<int>odp,stos;

bool check(int l, int r)
{
    odp.clear();
    stos.clear();
    for(int i=l;i<=r;++i)
    {
        int tabi = tab[i];
        if(!odp.empty() && tabi<odp.back())
            return 0;
        while(!stos.empty() && tabi>stos.back())
        {
            odp.pb(stos.back());
            stos.pop_back();
        }
        stos.pb(tabi);
    }
    return 1;
}
bool check_mask(int mask)
{
    vector<int>p;
    for(int i=0;i<n-1;++i)
        if(mask & (1LL << i))
            p.pb(i+1);
    p.pb(n);
    int last = 1;
    for(auto x : p)
    {
        if(check(last, x)==0)
            return 0;
        last = x + 1;
    }
    return 1;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    if(n>20) return 13;
    for(int i=1;i<=n;++i)
        cin>>tab[i];

    int solv = n;
    for(int mask = 0; mask < (1LL << (n-1)); ++mask)
    {
        if(check_mask(mask))
            solv = min(solv, (int)__builtin_popcount(mask)+1);
    }
    cout<<solv<<"\n";
    return 0;
}