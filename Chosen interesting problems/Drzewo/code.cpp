#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long

constexpr int maxn=1e5+7;

int n,m;
int a,b;
int solv;

vector<pair<int,pair<int,int>>>edge;

int rep[maxn];
void set_rep()
{
    for(int i=1;i<maxn;i++)
        rep[i]=i;
}

int Find(int x)
{
    if(rep[x]==x) return x;
    else return rep[x]=Find(rep[x]);
}

void Union(int a, int b)
{
    rep[Find(a)]=rep[Find(b)];
}


int min_vertex[maxn];

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        edge.push_back({a+b,{a,b}});
    }

    sort(edge.begin(), edge.end(), greater<pair<int,pair<int,int>>>());

    set_rep();
    for(int i=0;i<edge.size();i++)
    {
        a = edge[i].s.f;
        b = edge[i].s.s;

        if(Find(a)!=Find(b))
            Union(a,b);
        else
            solv += a+b;
    }
    for(int i=2;i<=n;i++)
    {
        if(Find(1)!=Find(i))
        {
            Union(1,i);
            solv+=1+i;
        }
    }
    cout<<solv;
    return 0;
}