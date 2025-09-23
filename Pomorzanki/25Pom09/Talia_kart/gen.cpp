#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ld long double

#define pi pair<int,int>
#define f first
#define s second
#define pb push_back
#define sz(A) (int)A.size()

constexpr int inf = 1e9+7;
constexpr int maxn = 17;

int n;
char C[maxn];
int R[maxn];
int B[maxn];

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N = 16;
    int W = 1e7;

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distribN(N-2, N);
    std::uniform_int_distribution<> distribC(1, 2);
    std::uniform_int_distribution<> distrib(1, W);

    n = distribN(g);
    cout<<n<<'\n';
    for(int i=1;i<=n;++i)
    {
        if(distribC(g)==1)
            cout<<"R ";
        else
            cout<<"B ";
        cout<<distrib(g)<<' '<<distrib(g)<<'\n';
    }
    return 0;
}