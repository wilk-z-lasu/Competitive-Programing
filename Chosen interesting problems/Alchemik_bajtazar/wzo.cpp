#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;

int n,a,b;
int m1,m2;
vector<int>vec1[maxn];
vector<int>vec2[maxn];

bool connected1[maxn];
bool connected2[maxn];

vector<pair<char, pi>>solv;
map<pi,bool>have1;
map<pi,bool>have2;

bool vis1[maxn];
void dfs1(int v=1)
{
    // cout<<v<<": "<<connected1[v]<<endl;
    if(!connected1[v])
        solv.pb({'+', {1,v}});
    vis1[v]=1;
    for(auto &u: vec1[v])
        if(!vis1[u])
            dfs1(u);
}
bool vis2[maxn];
void dfs2(int v=1)
{
    vis2[v]=1;
    for(auto &u: vec2[v])
        if(!vis2[u])
            dfs2(u);
    if(!connected2[v])
        solv.pb({'-', {1,v}});
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    cin>>m1;
    for(int i=1;i<=m1;++i)
    {
        cin>>a>>b;
        if(a>b) swap(a,b);
        if(a==1) connected1[b]=1;
        else have1[{a,b}]=1;
        vec1[a].pb(b);
        vec1[b].pb(a);
    }
    cin>>m2;
    for(int i=1;i<=m2;++i)
    {
        cin>>a>>b;
        if(a>b) swap(a,b);
        if(a==1) connected2[b]=1;
        else have2[{a,b}]=1;
        vec2[b].pb(a);
        vec2[a].pb(b);
    }
    connected1[1]=1;
    connected2[1]=1;

    dfs1();
    for(auto &u: have1)
    {
        a = u.f.f;
        b = u.f.s;
        if(!have2[{a,b}])
            solv.pb({'-', {a,b}});
        else
            have2[{a,b}]=0;
    }
    for(auto &u: have2)
    {
        if(!u.s) continue;
        // cout<<u.f.f<<" "<<u.f.s<<"\n";
        solv.pb({'+', {u.f.f, u.f.s}});
    }
    dfs2();

    cout<<sz(solv)<<"\n";
    for(auto &u: solv)
        cout<<u.f<<" "<<u.s.f<<" "<<u.s.s<<"\n";
    return 0;
}