#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=15+7;

int n,m;
int A[maxn],W[maxn];

int check(vector<pi>& vec)
{
    for(int i=0;i+1<sz(vec);++i)
        if(vec[i].f == vec[i+1].f)
            return 0;
    int odp=0;
    for(auto x:vec)
        odp+=x.s;
    return odp;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    cin>>m;
    for(int i=1;i<=n;++i)
        cin>>A[i]>>W[i];

    int solv = 0;
    for(int mask = 0; mask < (1ll<<n); ++mask)
    {
        int tmp=mask;
        vector<pi>vec;
        for(int i=1;i<=n;++i)
        {
            if(tmp&1)
                vec.pb({A[i], W[i]});
            tmp/=2;
        }
        solv = max(solv, check(vec));
    }
    cout<<solv<<"\n";
    return 0;
}