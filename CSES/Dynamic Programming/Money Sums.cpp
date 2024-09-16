#include <bits/stdc++.h>
using namespace std;

constexpr int maxi=1e6+7;

bitset<maxi> dp;
int n;
int x;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    dp[0]=1;
    cin>>n;
    while(n--)
    {
        cin>>x;
        dp |= (dp<<x);
    }
    cout<<dp.count()-1<<'\n';
    for(int i=1;i<maxi;i++)
        if(dp[i])
            cout<<i<<' ';
}