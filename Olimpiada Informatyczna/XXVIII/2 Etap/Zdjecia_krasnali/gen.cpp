#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 20+7;

int n,m;

int a,b;
vector<int>vec[maxn];

int vis[maxn];

bool check()
{
    for(int i=1;i<=n;++i)
        if(vis[i]%2==1)
            return 0;
    return 1;
}
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    n = 7;
    
    std::random_device rd;
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(n-2, n+2);// od n-2 do n+2
    m = distrib(gen);    

    vector<pi>s;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
            s.pb({i,j});

    do
    {
        std::mt19937 g(rd());
        std::shuffle(s.begin(), s.end(), g);
        for(int i=1;i<=n;++i)
            vis[i]=0;
        
        for(int i=0;i<m;++i)
        {
            vis[s[i].f]++;
            vis[s[i].s]++;
        }
    }
    while(!check());

    cout<<n<<' '<<m<<'\n';
    for(int i=0;i<m;++i)
        cout<<s[i].f<<' '<<s[i].s<<'\n';
    return 0;
}