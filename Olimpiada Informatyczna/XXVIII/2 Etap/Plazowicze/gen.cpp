
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 1e6+7;

int n,X,z,k;
int x[maxn];

int Get(int a, int b)
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(a, b);
    return distrib(gen);
}

int32_t main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    n = Get(2, 1e5);
    X = Get(2e5, 1e9);
    z = Get(1,5);
    
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, X-1);
    
    map<int,bool>have;
    while(sz(have) < n-2)
        have[distrib(gen)] = 1;
    
    cout<<n<<' '<<X<<' '<<z<<'\n';
    cout<<0<<' ';
    for(auto &it: have)
        cout<<it.f<<' ';
    cout<<X<<'\n';
    for(int i=1;i<=z;++i)
        cout<<Get(1,n)<<'\n';
    return 0;
}