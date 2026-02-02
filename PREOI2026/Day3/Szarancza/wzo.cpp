#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long
// #define ll long long
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int maxn=2e5+7;
constexpr int maxm=4e5+7;
constexpr int mod=1e9+7;

int n,m;
int a,b,w;

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

vector<pi> vec[maxn];

int tin[maxn];
int tout[maxn];
int Time = 0;
void licz_time(int v=1, int ojciec=-1)
{
    tin[v] = ++Time;
    for(auto &u: vec[v])
    {
        if(u.f == ojciec) continue;
        licz_time(u.f,v);
    }
    tout[v] = ++Time;
}

map<int, pair<pi,pi>>mp;

bool is_subtree(int v1, int v2) //is v2 in subtree[v1]
{
    if(tin[v1] <= tin[v2] && tout[v2] <= tout[v1])
        return true;
    return false;
}
int solv = 0;
void dfs(int v=1, int ojciec=-1, int up=-1)
{
    if(up != -1)
    {
        if(mp[up].f == mp[up].s)
            ++solv;
        else
        {
            if(tin[mp[up].f.f] > tin[mp[up].f.s]) swap(mp[up].f.f,mp[up].f.s);
            if(tin[mp[up].s.f] > tin[mp[up].s.s]) swap(mp[up].s.f,mp[up].s.s);
            if(mp[up].f.s!=v) swap(mp[up].f, mp[up].s);

            if(is_subtree(v,mp[up].s.f)^is_subtree(v,mp[up].s.s))
                ++solv;
        }
    }
    for(auto &u: vec[v])
    {
        if(u.f == ojciec) continue;
        dfs(u.f, v, u.s);
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;

    vector<pair<int,pi>> List;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b>>w;
        if(a==b) continue;
        if(a>b) swap(a,b);
        List.pb({w, {a,b}});
        if(mp.find(w) == mp.end())
        {
            mp[w] = {{a,b}, {0,0}};
        }
        else
        {
            mp[w].s.f = a;
            mp[w].s.s = b;
        }
    }

    sort(List.begin(),List.end());
    prepare();
    for(int i=1;i<=sz(List);++i)
    {
        w = List[i-1].f;
        a = List[i-1].s.f;
        b = List[i-1].s.s;
        if(Find(a) != Find(b))
        {
            Union(a,b);
            vec[a].pb({b,w});
            vec[b].pb({a,w});
        }
    }

    licz_time();
    dfs();

    int odp = 1;
    while(solv--)
        odp = (odp * (int)2) % mod;
    cout<<odp;
    return 0;
}