#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define ll long long
#define ld long double

#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=1e5+7;

int n;
pi p[maxn];
vector<pair<ll, pi>> edges;

const ld PI = std::acos(-1);

ll dist(int i1, int i2)
{
    return (ll)(p[i1].f - p[i2].f) * (ll)(p[i1].f - p[i2].f) + (ll)(p[i1].s - p[i2].s) * (ll)(p[i1].s - p[i2].s);
}

int rep[maxn];
int siz[maxn];
int odl[maxn]; // 0 - parzysta odleglosc, 1 - nieparzysta

void prepere()
{
    for(int i=1;i<=n;i++)
    {
        rep[i] = i;
        siz[i] = 1;
        odl[i] = 0;
    }
}

int Find(int x)
{
    if(x == rep[x]) return x;
    int root = Find(rep[x]);
    odl[x] ^= odl[rep[x]]; // aktualizuj parzystosc
    rep[x] = root;
    return root;
}

void Union(int a, int b)
{
    int ra = Find(a);
    int rb = Find(b);
    if(siz[ra] < siz[rb]) swap(ra, rb);
    rep[rb] = ra;
    siz[ra] += siz[rb];
    odl[rb] = odl[a] ^ odl[b] ^ 1; // ustawiamy nieparzysta odleglosc miedzy a i b
}
bool cmp(pi &a, pi &b)
{
    ll d1 = dist(a.f, a.s);
    ll d2 = dist(b.f, b.s);
    if(d1 != d2)
        return d1 < d2;
    else if(a.f != b.f)
        return a.f < b.f;
    else
        return a.s < b.s;
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>p[i].f>>p[i].s;

    int times1=7;
    int times2=5;

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 2*PI);
    edges.reserve(n * times1 * times2);
    while(times1--)
    {
        ld angle = dis(gen);
        vector<pair<ld,int>> projected;
        for(int i=1;i<=n;++i)
        {
            int new_x = p[i].f * cos(angle) - p[i].s * sin(angle);
            projected.pb({new_x, i});
        }
        sort(projected.begin(), projected.end());
        for(int i=0;i<sz(projected);++i)
            for(int j=i+1;j<sz(projected) && j<=i+times2;++j)
                    edges.pb({dist(projected[i].s, projected[j].s), {projected[i].s, projected[j].s}});
    }
   
    sort(edges.begin(), edges.end());

    prepere();
    for(auto &e : edges)
    {
        ll d = e.f;
        int v = e.s.f;
        int u = e.s.s;
        if(Find(u) == Find(v))
        {
            if((odl[u] ^ odl[v]) == 0)
            {
                cout<<d;
                return 0;
            }
        }
        else
            Union(u, v);
    }
    return 0;
}