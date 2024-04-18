#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

#define float long double

int N,K;
int dp[20];

void f(int l, int k, int p=0)//l-lit k-k p-prz
{
    for(int i=1;i<=l;++i)//i <- literka graniczna
    {
        if(dp[i-1]*dp[l-i]<=k)
            k-=dp[i-1]*dp[l-i];
        else
        {
            char odp='a'-1+p+i;cout<<odp;
            f(i-1,k/dp[l-i],p);
            f(l-i,k%dp[l-i],p+i);
            break;
        }
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>K;
    swap(N,K);
    K--;

    dp[0]=1;
    for(int i=1;i<=19;i++)
        for(int nowe=1;nowe<=i;nowe++)
            dp[i]+=dp[nowe-1]*dp[i-nowe];

    f(N,K);
    return 0;
}