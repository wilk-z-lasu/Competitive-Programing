#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
// #define int long long

int n,m,k;
int a,b;

constexpr int maxn = 1e6+7;// maksymalny number elementow które będziemy łączyć

int rep[maxn];

void set_rep()
{
    for(int i=0;i<maxn;++i)
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

vector<pair<int,int>> roz;
vector<pair<int,int>> block;

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	set_rep();

	cin>>n>>m>>k;

	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		if(a>k)
			Union(a,b);
		else
			roz.push_back({a,b});
	}

	for(auto u: roz)
	{
		a=u.f; b=u.s;
		if(Find(a)!=Find(b))
			Union(a,b);
		else
			block.push_back({a,b});
	}
	cout<<block.size()<<'\n';
	for(auto u: block)
		cout<<u.f<<" "<<u.s<<'\n';

	return 0;
}