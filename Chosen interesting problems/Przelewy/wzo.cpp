#include <bits/stdc++.h>
using namespace std;

#define int long long

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

constexpr int maxn=1e6+7;
constexpr int inf=8e18+7;

int n,x;
int a,b;
int tab[maxn];
vector<int>vec[maxn];

void chceck_possibility()
{
    int sum=0;
    for(int i=1;i<=n;++i)
        sum+=tab[i];
    if(sum!=0)
    {
        cout<<"NIE";
        exit(0);
    }
}

int sum_subtree[maxn];
int S[maxn];
void dfs(int v=1, int ojciec=1)
{
    sum_subtree[v]=tab[v];
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        dfs(u,v);
        sum_subtree[v]+=sum_subtree[u];
    }
    if(v==1) return;
    if(sum_subtree[v]>=0)
    {
        S[v] = sum_subtree[v];
    }
    else
    {
        S[1] += abs(sum_subtree[v]);
        S[v] -= abs(sum_subtree[v]);
    }
}
int min_S=inf;
void Push(int v=1, int ojciec=1)
{
    min_S = min(min_S, S[v]);
    for(auto &u: vec[v])
    {
        if(u==ojciec) continue;
        S[u] += S[v];
        Push(u,v);
    }
}
__int128 odp=0;
void Print(__int128 x)
{
    if(x==0)
    {
        cout<<0;
        return;
    }
    vector<int>V;
    while(x)
    {
        V.pb(x%10);
        x/=10;
    }
    reverse(V.begin(),V.end());
    for(auto &el: V)
        cout<<el;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>x;
        tab[i]+=x;
    }
    for(int i=1;i<=n;++i)
    {
        cin>>x;
        tab[i]-=x;
    }
    chceck_possibility();
    for(int i=1;i<=n-1;++i)
    {
        cin>>a>>b;
        vec[a].pb(b);
        vec[b].pb(a);
    }

    dfs();
    Push();

    for(int i=1;i<=n;++i)
        odp += (S[i]-min_S);

    cout<<"TAK\n";
    Print(odp);
    return 0;
}