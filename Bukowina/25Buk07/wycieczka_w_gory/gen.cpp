#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 1e5+7;

int n,k;

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(4, 7);
    std::uniform_int_distribution<> Cost(1, 6);

    n=distrib(gen);
    k=4;
    cout<<n<<' '<<k<<endl;

    vector<int>akt={1};
    for(int i=2;i<=n;++i)
    {
        std::uniform_int_distribution<> Prev(0, i-2);
        cout<<akt[Prev(gen)]<<' '<<i<<' '<<Cost(gen)<<endl;
        akt.pb(i);
    }

}