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
int n;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribN(1, 3);
    std::uniform_int_distribution<> distrib(1, 5);

    n = distribN(gen);
    cout << n << "\n";
    for(int i=1;i<=n;++i)
    {
        int a = distrib(gen);
        int b = distrib(gen);
        if(a > b) swap(a, b);
        cout << a << " " << b<< "\n";
    }
}