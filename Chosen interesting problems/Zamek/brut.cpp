#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define f first
#define s second
#define pb push_back
#define pi pair<int,int>
#define sz(A) (int)(A.size())

const int maxn=1e5+7;
int n, m, q;
int a,b,c;
vector<pair<int,pi>>edges;

int rep[maxn];
//find&union
int Find(int x)
{
    if(rep[x]==x) return x;
    return rep[x]=Find(rep[x]);
}
void Union(int a,int b)
{
	a=Find(a);
	b=Find(b);
    if(a==b) return;
    rep[a]=rep[b];
}
void prepere()
{
    for(int i=0;i<=n+3;i++)
        rep[i]=i;
}

bool used[maxn];
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i=1;i<=m;++i)
    {
        cin>>a>>b>>c;
        edges.pb({c,{a,b}});
    }
    sort(edges.begin(), edges.end());

    cin>>q;
    for(int i=1;i<=q;++i)
    {
        int odp=0;
        cin>>a>>b;
        prepere();
        Union(a,b);
        for(auto &e: edges)
        {
            int x=e.s.f;
            int y=e.s.s;
            int w=e.f;
            if(Find(x)!=Find(y))
            {
                Union(x,y);
                odp+=w;
            }
        }
        bool possible=1;
        for(int i=2;i<=n;++i)
            if(Find(1)!=Find(i))
                possible=0;
        if(possible)
            cout<<odp<<'\n';
        else
            cout<<"Ojojoj\n";
    }
}