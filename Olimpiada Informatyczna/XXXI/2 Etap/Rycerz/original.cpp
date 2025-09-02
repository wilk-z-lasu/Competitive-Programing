// XXXI Olimpiada Informatyczna - 2 Etap
// Mateusz Woloszyk
// Solution for 25/100 pkt
//rozwiazanie na 75
#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

constexpr int inf=1e9+7;
constexpr int maxn=1000+7;//zmienic jak chce na 100
constexpr int maxm=1000+7;//zmienic jak chce na 100
constexpr int maxk=11;

int n,m,d,k;

vector<int> maxi(vector<int>&x1,vector<int>&x2)
{
	for(int i=0;i<x1.size();i++)
	{
		if(x1[i]>x2[i])
			return x1;
		if(x1[i]<x2[i])
			return x2;
	}
	return x1;//sa takie same
}
vector<int> polacz(vector<int>&x1,vector<int>&x2)
{
	vector<int> solv;
	for(int i=0;i<x1.size();i++)
		solv.push_back(max(x1[i],x2[i]));
	return solv;
}

map<pair<int,vector<int>>,int>was;

vector<pair<int,vector<int> > >graf1[11];
vector<int>solv;
void dfs(int v,int koszt, vector<int>ust)
{
	if(koszt<=d && v==n)
		solv=maxi(solv,ust);
	if(koszt>d) return;
	for(auto &p: graf1[v])
	{
		if(was.find({p.f,polacz(ust,p.s)})==was.end() || koszt+1<was[{p.f,polacz(ust,p.s)}])
		{
			was[{p.f,polacz(ust,p.s)}]=koszt+1;
			dfs(p.f,koszt+1,polacz(ust,p.s));
		}
	}
}

int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin>>n>>m>>d>>k;

	if(k==1)//podzadanie 2
	{
		int u,v,miecz;
		vector<pair<int,pair<int,int>>>vec;
		vector<int>graf[10007];
		int odl_1[10007];
		int odl_n[10007];
		for(int i=0;i<10007;i++)
		{
			odl_1[i]=inf;
			odl_n[i]=inf;
		}
		for(int j=1;j<=m;j++)
		{
			cin>>u>>v>>miecz;
			graf[u].push_back(v);
			graf[v].push_back(u);
			vec.push_back({miecz,{u,v}});
			vec.push_back({miecz,{v,u}});
		}

		queue<pair<int,int>>q;
		q.push({1,0});
		odl_1[1]=0;
		while(!q.empty())
		{
			for(auto &p: graf[q.front().f])
			{
				if(odl_1[p]==inf)
				{
					odl_1[p]=q.front().s+1;
					q.push({p,odl_1[p]});
				}
			}
			q.pop();
		}

		q.push({n,0});
		odl_n[n]=0;
		while(!q.empty())
		{
			for(auto &p: graf[q.front().f])
			{
				if(odl_n[p]==inf)
				{
					odl_n[p]=q.front().s+1;
					q.push({p,odl_n[p]});
				}
			}
			q.pop();
		}
		sort(vec.begin(),vec.end(),greater<pair<int,pair<int,int>>>());

		for(auto &g: vec)
		{
			if(odl_1[g.s.f]+odl_n[g.s.s]+1<=d)
			{
				cout<<g.f;
				return 0;
			}
		}
	}
	if(n<=10 && m<=10 && d<=10)//podzadanie 1
	{
		for(int i=1;i<=k;i++)
			solv.push_back(0);
		int u,v;
		int a;
		int tab[11][11];//[nr krawedzi]
		for(int j=1;j<=m;j++)
		{
			cin>>u>>v;
			vector<int>h;
			for(int i=1;i<=k;i++)
			{
				cin>>a;
				h.push_back(a);
			}
			graf1[u].push_back({v,h});
			graf1[v].push_back({u,h});
		}
		dfs(1,0,solv);
		for(auto &pom: solv)
			cout<<pom<<' ';
		return 0;
	}

	return 0;
}