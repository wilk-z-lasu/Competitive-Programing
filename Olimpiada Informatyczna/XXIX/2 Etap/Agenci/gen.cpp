#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn = 5e5+7;
constexpr int inf = 1e9+7;

int n,k;
int a,b;

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(3, 6);

    n = distrib(gen);
    std::uniform_int_distribution<> distribN(1, n);

    k = distribN(gen);

    cout<<n<<' '<<k<<endl;

    vector<int> agent;
    for(int i=1;i<=n;++i)
        agent.push_back(i);
    shuffle(agent.begin(), agent.end(), gen);
    for(int i=1;i<=k;++i)
        cout<<agent[i-1]<<' ';
    cout<<endl;

    for(int i=2;i<=n;++i)
    {
        std::uniform_int_distribution<> Dprev(1, i-1);
        cout<< Dprev(gen) <<' '<<i<<endl;
    }
}