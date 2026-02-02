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
int n,m;


int rep[maxn];
void prepare()
{
    for(int i=1;i<=n;++i)
        rep[i]=i;
}
int Find(int x)
{
    if(x==rep[x]) return x;
    else return rep[x] = Find(rep[x]);
}
void Union(int A, int B)
{
    A = Find(A);
    B = Find(B);
    rep[A] = B;
}

bool diff_find()
{
    for(int i=1;i<=n;++i)
        if(Find(i) != Find(1))
            return true;
    return false;
}

map<int,bool> taken;
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(2, 8);
    std::uniform_int_distribution<> distribL(1, 1000);

    n = distrib(gen);
    std::uniform_int_distribution<> distribN(1, n);
    vector<pair<pi,int>>zap;

    prepare();
    while(diff_find())
    {
        pi p1 = {distribN(gen), distribN(gen)};
        pi p2 = {distribN(gen), distribN(gen)};
        int w = distribL(gen);
        while(taken[w])
            w = distribL(gen);
        taken[w] = true;

        zap.pb({p1, w});
        zap.pb({p2, w});
        Union(p1.f, p1.s);
        Union(p2.f, p2.s);
    }
    cout<<n<<' '<<sz(zap)<<'\n';
    for(auto &x: zap)
        cout<<x.f.f<<' '<<x.f.s<<' '<<x.s<<'\n';
    return 0;
}