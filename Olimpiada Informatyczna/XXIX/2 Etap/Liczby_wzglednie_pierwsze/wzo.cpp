#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

int N,K,C;

vector<int> primes;
void get_primes(int maxn)
{
    vector<bool> is_prime(maxn+7, true);
    is_prime[0] = is_prime[1] = false;
    for(int i=2;i<=maxn;i++)
    {
        if(is_prime[i])
        {
            primes.pb(i);
            for(int j=i*i;j<=maxn;j+=i)
                is_prime[j] = false;
        }
    }
}
vector<int>vec;
void gen_div(int n)
{
    for(auto &p: primes)
        if(n%p == 0)
        {
            vec.pb(p);
            while(n%p == 0)
                n/=p;
        }
    if(n!=1)
        vec.pb(n);
}
int sym(int k)
{
    int nums=k;
    for(int mask=1; mask<(1<<(sz(vec))); ++mask)
    {
        int prod = 1;
        int ile = 0;
        for(int i=0;i<sz(vec);++i)
            if(mask&(1<<i))
            {
                prod *= vec[i];
                ++ile;
            }
        if(ile&1)
            nums -= k/prod;
        else
            nums += k/prod;
    }
    return nums;
}
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>N>>K>>C;

    int S=1;
    while((S+1)*(S+1) <= N)
        ++S;

    get_primes(S);
    gen_div(N);

    int l = 1;
    int r = 1e16;

    // for(auto &u: vec)
    //     cout<<u<<endl;
    
    while(l<r)
    {
        int mid = (l+r)/2;
        if(sym(mid) < K)
            l = mid+1;
        else
            r = mid;
    }
    cout<<l<<' ';
    while(--C)
    {
        while(__gcd(++l,N)!=1);
        cout<<l<<' ';
    }
    return 0;
}