#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=18;
int mod;

int n,m;
int a,b;

vector<int>vec[maxn];

int bits[1<<maxn];
int possible[1<<maxn];
int dp[1<<maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    if(n>0) mod = 998244353;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b; a--; b--;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }

    for(int i=0;i<(1<<n);i++)
        bits[i] = __builtin_popcount(i);

    for(int i=0;i<(1<<n);i++)
        possible[i]=1;

    for(int i=0;i<(1<<n);i++)//O(2^n)
        for(int j=0;j<n;j++)//O(n)
            if(i & (1<<j))
                for(auto &u: vec[j])
                    if(i & (1<<u))
                        possible[i]=0;

    dp[0] = 1;
    for(int mask=1;mask<(1<<n); ++mask)
    {
        // cout<<"mask: "<<mask<<endl;
        for(int i = mask; i > 0; i = (i-1) & mask)
        {
            if(possible[i])
            {
                // cout<<"-"<<i<<endl;
                if(bits[i]%2==1)
                    dp[mask] += dp[mask xor i];
                else
                    dp[mask] -= dp[mask xor i];
            }
        }
    }

    cout<<(dp[(1<<n)-1]/2 * m)%mod;
    return 0;
}