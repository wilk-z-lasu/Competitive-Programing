#include<bits/stdc++.h>
using namespace std;
// #define int long long

#define f first
#define s second
#define pi pair<int,int>
#define sz(A) (int)(A.size())
#define pb push_back


constexpr int maxn=2e5+7;

int n,q;

vector<pair<int, pi>>zap[maxn];
vector<pair<int, pi>>vec[maxn];

int solv[maxn];

int rep[maxn];
int siz[maxn];
void prepere()
{
	for(int i=0;i<maxn;++i)
	{
		rep[i]=i;
		siz[i]=1;
	}
}
int Find(int x)
{
	if(rep[x]==x) return rep[x];
	else return Find(rep[x]);
}
vector<pair<pi,pi>>r;
void Union(int a, int b)
{
	a = Find(a);
	b = Find(b);

	// if(a==b) return;

	if(siz[a] < siz[b]) swap(a,b); //siz[a] >= siz[b]

	r.pb({{a,siz[a]},{b,rep[b]}});
	siz[a] += siz[b];
	rep[b] = a;
}
void rollback()
{
	int a=r.back().f.f;
	int new_size=r.back().f.s;
	int b=r.back().s.f;
	int new_rep=r.back().s.s;

	siz[a] = new_size;
	rep[b] = new_rep;

	r.pop_back();
}
void dfs(int i=0)
{
	for(auto &e: zap[i])
	{
		int id = e.f;
		int u = e.s.f;
		int v = e.s.s;
		if(Find(u) == Find(v))
			solv[id]=1;
		else
			solv[id]=0;
	}
	for(auto &e: vec[i])
	{
		int id = e.f;
		int u = e.s.f;
		int v = e.s.s;
		Union(u,v);
		// cout<<i<<" -> "<<id<<": "<<u<<" <-> "<<v<<endl;
		dfs(id);
	}
	if(i!=0)
		rollback();
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>q;

	for(int i=1;i<=q;++i)
	{
		int t,k,u,v;
		cin>>t>>k>>u>>v;
		k++;

		if(t==1)
			zap[k].pb({i,{u,v}});
		else
			vec[k].pb({i,{u,v}});
	}
	for(int i=1;i<=q;++i) solv[i]=-1;
	prepere();
	dfs();
	for(int i=1;i<=q;++i)
		if(solv[i]!=-1)
			cout<<solv[i]<<'\n';
	return 0;
}