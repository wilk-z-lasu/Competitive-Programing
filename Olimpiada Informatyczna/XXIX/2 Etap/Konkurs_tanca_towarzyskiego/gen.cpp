#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxq = 5000+7;
constexpr int inf = 1e9+7;

int q;
int c;
int it = 2;

int get_random(int a, int b)
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

    q = get_random(1, 10);

    cout<<q<<'\n';
    while(q--)
    {
        c = get_random(1, 3);
        if(c==1)
            cout<<"? "<<get_random(1, it)<<'\n';
        if(c==2)
        {
            cout<<"Z "<<get_random(1, it)<<'\n';
            ++it;
        }
        if(c==3)
        {
            cout<<"W "<<get_random(1, it)<<'\n';
            ++it;
        }
    }

    return 0;
}