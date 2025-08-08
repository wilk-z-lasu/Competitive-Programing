#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

int n,k,c;

void get_primes()
{
    int maxn=50; // Adjust this value as needed
    vector<int> primes;
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
    // for(auto &u: primes)
    //     cout << u << " ";
    // cout << endl;

    int num = 1;
    for(auto &u: primes)
    {
        num *= u;
        cout << num << " ";
    }
    cout << endl;
}
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // cin>>n>>k>>c;

    get_primes();
    return 0;
}