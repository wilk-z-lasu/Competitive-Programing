#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long

#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e6 + 7;
int n,k;
int a;
vector<int>group[maxn];
int solv;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;++i)
    {
        cin>>a;
        group[a].pb(i);
    }

    for(int i=1;i<=n;++i)
    {
        if(group[i].empty()) continue;

        vector<int>costs = {0};
        for(int j=1;j<sz(group[i]);++j)
            costs.pb(group[i][j] - group[i][j-1] - 1);
        
        int sum = 0;
        int p = 0;
        for(int l = 0; l < sz(costs); ++l)
        {
            while(p+1 < sz(costs) && sum + costs[p+1] <= k)
            {
                sum += costs[p+1];
                p++;
            }
            solv = max(solv, p - l + 1);
            sum -= costs[l+1];
        }
    }
    cout<<solv;
    return 0;
}