#include <bits/stdc++.h>
using namespace std;

#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=500007;
constexpr int inf=1e9+7;

int N,S;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(2, 10);

    N=distrib(gen);
    S=distrib(gen);

    cout<<N<<" "<<S<<'\n';
    for(int i=1;i<=N;++i)
        cout<<distrib(gen)<<' ';
    return 0;
}