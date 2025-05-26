#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second

//HASHING DATA
constexpr int maxn = 1e6+7;
constexpr int mod = 1e9+7;
int p = 31;
int P[maxn];
int h[maxn];

//INPUT DATA
int n;
string w;

//CALCULATING DATA
int dp[maxn];

int get_hash(int a, int b)
{
    return (((h[b] - h[a-1] + mod)%mod) * P[n-a])%mod;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    cin>>w;
    w = '#' + w;

    P[0]=1;
    for(int i=1;i<=n;++i)
        P[i] = (P[i-1] * p)%mod;

    for(int i=1;i<=n;++i)
        h[i] = (h[i-1] + (w[i]-'a'+1)*P[i])%mod;

    if(n%2==0 && w[n/2]==w[n/2 + 1])
        dp[n/2]=1;

    for(int i=n/2; i>=1; --i)
    {
        int j = dp[i+1] + 2;
        j = min(j, (n/2 - i));

        while(j>=0 && get_hash(i, i+j)!=get_hash(n-(i+j)+1, n-i+1)) 
            --j;
        dp[i] = j+1;
    }

    int solv=0;
    for(int i=1;i<=n/2;++i)
        if(get_hash(1,i)==get_hash(n-i+1,n))
            solv = max(solv, i+dp[i+1]);
    cout<<solv;
    return 0;
}