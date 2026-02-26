#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=21;
int n, m;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 5);

    n = distrib(gen);
    m = distrib(gen);
    cout << n << " " << m << "\n";

    vector<int> vec;
    int maxi = distrib(gen);
    for (int i = 1; i <= n; ++i)
        if(maxi%i==0)
            vec.pb(i);
    
    std::uniform_int_distribution<> get_vec(0, sz(vec)-1);

    for(int i=1;i<=n;++i)
    {
        int v = distrib(gen);
        cout << distrib(gen) << " " << vec[get_vec(gen)] << "\n";
    }

}