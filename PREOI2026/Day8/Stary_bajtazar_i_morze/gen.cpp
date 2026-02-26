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
    std::uniform_int_distribution<> distrib(1, 4);
    std::uniform_int_distribution<> distribZ(0, 3);

    vector<char> znaki =  {'^', '>', 'v', '<'};

    n = distrib(gen);
    m = distrib(gen);
    cout << n << " " << m << "\n";

    std::uniform_int_distribution<> distribN(1, n);
    std::uniform_int_distribution<> distribM(1, m);

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cout << znaki[distribZ(gen)];
        }
        cout << "\n";
    }

    int q = distrib(gen);
    cout << q << "\n";
    for(int iter=1;iter<=q;++iter)
    {
        int a = distribN(gen);
        int b = distribM(gen);
        int c = distribN(gen);
        int d = distribM(gen);
        char Z = znaki[distribZ(gen)];
        cout << a << " " << b << " " << c << " " << d << " " << Z << "\n";
    }
}