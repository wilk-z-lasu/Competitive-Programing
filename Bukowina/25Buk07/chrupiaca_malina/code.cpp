#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

#define f first
#define s second
#define pi pair<int,int>
#define pb push_back
#define sz(A) (int)A.size()

constexpr int mod = 998244353;
constexpr int maxn = 2e5+7;

int t;
int n,m,k;
int a,b;

vector<pi>vec;

int pot(int c, int d) {
    int odp=1;
    while(d)
    {
        if(d&1)
            odp = (odp * c)%mod;
        c = (c*c)%mod;
        d/=2;
    }
    return odp;
}

int solv=1;
void Add(int w)
{
    solv = (solv * (pot(k-1,w) + (pot(-1, w) * (k-1))%mod + mod)%mod )%mod;
    solv = (solv * pot((k*(k-1))%mod, mod-2))%mod;
}

vector<int>graf[maxn];
void dfs(int v=0)
{
    int Siz = abs(vec[v].s+vec[v].f)+1;
    for(auto &u: graf[v])
    {
        Siz -= abs(vec[u].s+vec[u].f)-1;
        dfs(u);
    }
    // cout<<v<<": "<<Sizs<<endl;
    Add(Siz);
}

void clear() {
    solv = 1;
    vec.clear();
    for(int i=0;i<=m;++i)
        graf[i].clear();
}

void test() {
    for(int i=0;i<sz(vec);++i)
    {
        cout<<i<<": \n";
        for(auto j: graf[i])
            cout<<j<<' ';
        cout<<endl;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    while(t--)
    {
        cin>>n>>m>>k;
        clear();
        for(int i=1;i<=m;++i)
        {
            cin>>a>>b;
            if(b < a) swap(a,b);
            vec.push_back({a,-b});
        }
        vec.pb({0,n-1});
        sort(vec.begin(), vec.end());

        vector<pair<int,pi>>S;
        S.push_back({0,{-n,n}});
        for(int i=1;i<sz(vec);++i)
        {
            a = vec[i].f;
            b = -vec[i].s;
            while(S.back().s.s < b)
                S.pop_back();
            graf[S.back().f].pb(i);
            S.push_back({i,{a,b}});
        }
        
        dfs();
        cout<<((solv*k)%mod*(k-1))%mod<<'\n';
    }
    
}