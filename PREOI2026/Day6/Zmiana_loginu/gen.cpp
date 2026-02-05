#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

int n,m;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribN(1, 10);
    std::uniform_int_distribution<> distrib(1, 3);

    n = distribN(gen);

    vector<int>vec;
    cout<<n<<'\n';
    for(int i = 1; i <= n; ++i)
    {
        int x = distrib(gen);
        vec.pb(i+x);
        if(x == 1)
            cout<<'A';
        if(x == 2)
            cout<<'G';
        if(x == 3)
            cout<<'S';
    }
    cout<<'\n';
    shuffle(vec.begin(), vec.end(), gen);
    for(int i=1;i<=n;++i)
    {
        int x = vec[i-1];
        if((x-i + 300000)%3 == 1)
            cout<<'A';
        if((x-i + 300000)%3 == 2)
            cout<<'G';
        if((x-i + 300000)%3 == 0)
            cout<<'S';
    }
    cout<<'\n';
}
