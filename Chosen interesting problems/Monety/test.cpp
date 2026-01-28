#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e7+1;

void gen_primes(vector<int>& primes)
{
    vector<bool> is_prime(maxn,true);
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<maxn;i++)
    {
        if(is_prime[i])
        {
            if(i>=3) primes.pb(i);
            for(int j=i*i;j<maxn;j+=i)
                is_prime[j]=false;
        }
    }
}

map<int,int> dp;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> primes;
    gen_primes(primes);

    for(int i=0;i<sz(primes);i++)
        cout << primes[i] << ",";
    // cout << "\n";
    // for(int i=-maxn;i<maxn;i++) dp[i]=1e9;
    // dp[0]=0;
    // for(int p : primes)
    // {
    //     for(int i=-maxn;i<maxn;i++)
    //     {
    //         if(i-p >= -maxn) dp[i]=min(dp[i],dp[i-p]+1);
    //         if(i+p < maxn) dp[i]=min(dp[i],dp[i+p]+1);
    //     }
    // }
    // pair<int,int> maxi_pair={0,0};
    // for(int i=0;i<100;++i)
    // {
    //     // if(i%2==0 && dp[i]!=2) cout<<"Error at "<<i<<endl;
    //     cout<<"dp["<<i<<"] = "<<dp[i]<<"\n";
    //     // maxi_pair=max(maxi_pair,{dp[i],i});

    // }
    // // cout<<"dp["<<maxi_pair.s<<"] = "<<maxi_pair.f<<"\n";
}