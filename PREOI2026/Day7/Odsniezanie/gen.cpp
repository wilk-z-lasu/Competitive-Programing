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
int n,S;
map<pi, bool> taken;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribN(3, 7);

    n = distribN(gen);
    std::uniform_int_distribution<> distribS(1, n*n/2);
    std::uniform_int_distribution<> distribtoN(1, n);

    S = distribS(gen);

    cout << n <<" "<< S << "\n";
    for(int i=1;i<=S;++i)
    {
        pi p = {distribtoN(gen), distribtoN(gen)};
        while(taken[p])
            p = {distribtoN(gen), distribtoN(gen)};
        taken[p] = true;
        cout << p.f << " " << p.s << "\n";
    }
}