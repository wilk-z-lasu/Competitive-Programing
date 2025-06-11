#include <iostream>
using namespace std;

constexpr int maxn = 8007;
constexpr int mod = 1e9+7;

int n, dp[2][maxn], pre[maxn];

int main()
{
    cin>>n;

    getchar();

    for(int i=1;i<=n;++i)
    {
        dp[1][i]=1;
        pre[i]=i;
    }

    for(int preflix=2;preflix<=n;++preflix)
    {
        if(getchar()=='<')
        {
            for(int v=1;v<=preflix;++v)
                dp[preflix&1][v]=pre[v-1];
        }
        else
        {
            for(int v=1;v<=preflix;++v)
                dp[preflix&1][v]=(pre[preflix-1]-pre[v-1]+mod)%mod;
        }

        for(int i=1;i<=preflix+1;++i)
            pre[i]=(pre[i-1]+dp[preflix&1][i])%mod;
    }

    cout<<pre[n];
    return 0;
}