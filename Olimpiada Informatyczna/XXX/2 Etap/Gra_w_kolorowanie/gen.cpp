#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)A.size()

constexpr int maxn = 5e5+7;

int n;
int a,b;
int Sa, Sb, q;
char z, t;
int w;

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(4, 10);

    n = distrib(gen);
    cout<<n<<'\n';
    for(int i=2;i<=n;++i)
    {
        std::uniform_int_distribution<> A(1, i-1);
        cout<<A(gen)<<' '<<i<<'\n';
    }

    std::uniform_int_distribution<> distribN(1, n);
    int Sa = distribN(gen);
    int Sb = distribN(gen);
    int q=0;
    vector<int>vec;
    for(int i=1;i<=n;++i)
        vec.pb(i);
    cout<<Sa<<' '<<Sb<<' '<<q<<'\n';

    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
    for(int i=0;i<Sa;++i)
        cout<<vec[i]<<' ';
    cout<<'\n';
    std::shuffle(vec.begin(), vec.end(), g);
    for(int i=0;i<Sb;++i)
        cout<<vec[i]<<' ';
    cout<<'\n';
    while(q--)
    {
        //
    }
}