#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int unsigned long long

constexpr int inf=1e19;
int mod;

int n,a,b,d;

unordered_map<int,int>solutions;

inline int solv(int x)
{
    if(x==1)
        return 0;
    if(solutions.find(x)!=solutions.end()) return solutions[x];
    int l = x/2;
    int r = x - l;

    int odp = inf;
    while(l>0 && r-l<=d)
    {
        int solv_l = solv(l);
        int solv_r = solv(r);

        int odp2 =  solv_l + solv_r + min((a*r + b*l)%mod, (b*r + a*l)%mod);
        odp = min(odp, odp2);
        l--; r++;
    }
    return solutions[x]=odp;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>d>>a>>b;
    if(n>0) mod=1001;
    if(a>b) swap(a,b);
    cout<<solv(n);
    return 0;
}