#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1007;

int n,q;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribN(1, 100);
    std::uniform_int_distribution<> distrib(1, 5);


    n = distribN(gen);
    q = distribN(gen);

    std::uniform_int_distribution<> distribtoN(1, n);


    cout << n << " " << q << "\n";
    for(int i=1;i<=n;++i)
        cout << distrib(gen) << " ";
    cout << "\n";

    for(int i=1;i<=q;++i)
    {
        int l = distribtoN(gen);
        int r = distribtoN(gen);
        if(l>r) swap(l,r);
        int m = distribtoN(gen);
        std::uniform_int_distribution<> distribK(1, r-l+1);
        int k = distribK(gen);
        cout << l << " " << r << " " << m << " " << k << "\n";
    }
}