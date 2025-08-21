#include <bits/stdc++.h>
using namespace std;
// #define int long long

#define pb push_back
#define sz(A) (int)A.size()
#define pi pair<int,int>
#define f first
#define s second

constexpr int maxn = 207;

int n;
int a,b;
char c;

vector<pair<int,pair<int,char>>>vec[maxn];

vector<vector<char>>kan;
vector<char>szablon;
void gen_szablony(int v, int ojciec=-1)
{
    kan.pb(szablon);
    for(auto &u: vec[v])
    {
        if(u.f == ojciec) continue;
        szablon.pb(u.s.s);
        gen_szablony(u.f, v);
        szablon.pop_back();
    }
}

bool vis[maxn];
void clear_vis()
{
    for(int i=0;i<maxn;++i)
        vis[i]=0;
}
vector<char>akt;
bool check(int v, int ojciec=-1, int odl=0)
{
    if(odl == sz(akt)) return true;
    bool odp = false;
    for(auto &u: vec[v])
    {
        if((u.f == ojciec) || (u.s.s != akt[odl])) continue;
        if(check(u.f, v, odl+1))
        {
            vis[u.s.f] = true;
            odp = true;
        }
    }
    return odp;
}

set<vector<char>>solv;
void add_solv()
{
    for(int i=1;i<=n-1;++i)
        if(!vis[i])
            return;
    solv.insert(akt);
}
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b>>c;
        vec[a].pb({b, {i, c}});
        vec[b].pb({a, {i, c}});
    }

    int start;
    for(int i=1;i<=n;++i)
        if(sz(vec[i])==1)
            start=i;

    gen_szablony(start);

    // cout<<"start = "<<start<<endl;
    // for(auto &szablon: kan)
    // {
    //     for(auto &u: szablon)
    //         cout<<u;
    //     cout<<endl;
    // }

    for(auto &szablon: kan)
    {
        akt = szablon;
        clear_vis();
        for(int i=1;i<=n;++i)
            check(i);
        add_solv();
        reverse(akt.begin(), akt.end());
        add_solv();
    }
    cout<<sz(solv)<<'\n';
    for(auto &szablon: solv)
    {
        for(auto &u: szablon)
            cout<<u;
        cout<<'\n';
    }
    return 0;
}