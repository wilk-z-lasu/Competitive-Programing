#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int maxn=1007;
constexpr int inf=1e9+7;

int t[4];

int Q;
int p;

int dp[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t[1]>>t[2]>>t[3];
    dp[0]=0;
    for(int i=1;i<maxn;++i)
    {
        vector<int>vec;
        for(int pasek=1;pasek<=3;++pasek)
        {
            int siz = i-t[pasek];
            for(int j=0;j<=(siz/2 + siz%2);++j)
                vec.push_back(dp[j] xor dp[siz-j]);
        }
        vec.push_back(inf);
        sort(vec.begin(),vec.end());

        int last=-1;
        for(int j=0;j<vec.size();++j)
        {
            if(vec[j]-last > 1)
            {
                dp[i] = last+1;
                break;
            }
            last = vec[j];
        }
    }

    cin>>Q;
    while(Q--)
    {
        cin>>p;
        if(dp[p]!=0)
            cout<<1<<'\n';
        else
            cout<<2<<'\n';
    }
    return 0;
}