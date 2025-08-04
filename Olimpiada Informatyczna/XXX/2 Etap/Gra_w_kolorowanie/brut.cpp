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
vector<int>vec[maxn];

vector<int>kol;
bool dfs(int v, int cel, int ojciec=-1)
{
    if(v==cel)
    {
        kol.pb(v);
        return true;
    }
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        if(dfs(u,cel,v))
        {
            kol.pb(v);
            return true;
        }
    }
    return false;
}

bool block[maxn];
int get_siz(int v, int ojciec=-1)
{
    int odp=1;
    for(auto &u: vec[v])
    {
        if(u==ojciec || block[u]) continue;
        odp += get_siz(u,v);
    }
    return odp;
}
bool get_odp(int a, int b)
{
    kol.clear();
    dfs(a,b);

    if(sz(kol)==2)
    {
        block[kol[0]]=1;
        block[kol[1]]=1;
    }
    else
        block[kol[sz(kol)/2]]=1;

    int b_siz = get_siz(b);
    int a_siz = n - b_siz;
    if(sz(kol)==2)
    {
        block[kol[0]]=0;
        block[kol[1]]=0;
    }
    else
        block[kol[sz(kol)/2]]=0;

    return (a_siz > b_siz);
}

vector<int>A;
vector<int>B;
int solv()
{
    long long odp = 0;
    for(auto &x1: A)
        for(auto &x2: B)
            if(x1 != x2)
                if(get_odp(x1,x2))
                {
                    ++odp;
                    // cout<<x1<<" "<<x2<<endl;
                }
    return odp;
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n;

    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    cin>>Sa>>Sb>>q;

    

    while(Sa--)
    {
        cin>>w;
        A.pb(w);
    }
    while(Sb--)
    {
        cin>>w;
        B.pb(w);
    }
    cout<<solv()<<'\n';

    while(q--)
    {
        cin>>z>>t>>w;
    }
}