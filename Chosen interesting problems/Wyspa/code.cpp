#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f first
#define s second
#define pi pair<int,int>

constexpr int maxn=2e5+7;

int n,m,a,b;
int A[maxn];
vector<pair<int, pi>>vec;

int rep[maxn];
int siz[maxn];
vector<int>chances[maxn];
bool solv[maxn];

void prepere()
{
    for(int i = 0; i < maxn; i++)
    {
        rep[i] = i;
        siz[i] = A[i];
        chances[i].push_back(i);
    }
}

void add(vector<int> &x1, vector<int> &x2)
{
    for(auto &u: x2)
        x1.push_back(u);
}

int Find(int v)
{
    if(rep[v]==v) return v;
    else return rep[v]=Find(rep[v]);
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);

    if(chances[b].size() > chances[a].size()) swap(a,b);

    siz[a] += siz[b];
    add(chances[a], chances[b]);

    rep[b] = rep[a];
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>A[i];
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        if(A[a]<A[b]) swap(a,b);
        vec.push_back({A[a],{a,b}});
    }

    sort(vec.begin(), vec.end());

    prepere();
    for(auto [xd,p]: vec)
    {
        a = p.f;
        b = p.s;

        if(Find(a) == Find(b))
            continue;

        if(siz[Find(b)] < A[a])
            chances[Find(b)].clear();

        Union(a,b);
    }

    for(auto u: chances[Find(1)])
        solv[u] = 1;
    for(int i=1; i<=n; i++)
        cout<<solv[i];
    return 0;
}